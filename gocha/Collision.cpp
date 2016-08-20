
#include <vector>
#include <algorithm>
#include "Collision.h"
#include <math.h>

// ２つの矩形が衝突するかどうかを返す
static bool is_intersect_rects(int x_center1,int y_center1,int x_size1,int y_size1, 
							   int x_center2,int y_center2,int x_size2,int y_size2)
{
	int x_size1_half = x_size1 /2;
	int y_size1_half = y_size1 /2;
	int x_size2_half = x_size2 /2;
	int y_size2_half = y_size2 /2;
	int x1L = x_center1 - x_size1_half;
	int x1R = x_center1 + x_size1_half;
	int y1U = y_center1 - y_size1_half;
	int y1D = y_center1 + y_size1_half;
	int x2L = x_center2 - x_size2_half;
	int x2R = x_center2 + x_size2_half;
	int y2U = y_center2 - y_size2_half;
	int y2D = y_center2 + y_size2_half;
	return ! ( (x1R < x2L) || (x2R < x1L) || (y1D < y2U) || (y2D < y1U) );
}

// 初期化
void CollisionDetector::init(int fieldsize_x, int fieldsize_y, int gridspan_x, int gridspan_y)
{
	m_gridspan.Set(gridspan_x,gridspan_y);
	m_fieldsize.Set(fieldsize_x,fieldsize_y);
	m_gridcount.Set(
		((m_fieldsize.x - 1) / m_gridspan.x) + 1,
		((m_fieldsize.y - 1) / m_gridspan.y) + 1
		);
	m_grid.resize(m_gridcount.x * m_gridcount.y);
}

// オブジェクト（アクター）を衝突判定グリッドに追加
void CollisionDetector::add_object(int id, int x, int y, int w, int h)
{
	CollisionGridItem item(id, x, y, w, h);
	int w_half = w/2;
	int h_half = h/2;
	int cx1 = ((x - w_half) / m_gridspan.x);
	int cx2 = ((x + w_half) / m_gridspan.x);
	int cy1 = ((y - h_half) / m_gridspan.y);
	int cy2 = ((y + h_half) / m_gridspan.y);

	// オブジェクトの範囲がかかるすべてのセルにアクターを追加
	for (int ix = cx1 ; ix <= cx2 ; ix++) {
		for (int iy = cy1 ; iy <= cy2 ; iy++) {
			int cellpos = iy * m_gridcount.x + ix;
			if (cellpos < 0 || cellpos >= m_grid.size()) continue;
			std::vector< CollisionGridItem > & cell = m_grid[cellpos];
			cell.push_back(item);
		}
	}

}

// 近くにあるオブジェクトを収集
int CollisionDetector::search_near_objects(int x, int y, int w, int h, bool check_collision)
{
	m_results.clear();

	int w_half = w/2;
	int h_half = h/2;
	int cx1 = ((x - w_half) / m_gridspan.x);
	int cx2 = ((x + w_half) / m_gridspan.x);
	int cy1 = ((y - h_half) / m_gridspan.y);
	int cy2 = ((y + h_half) / m_gridspan.y);

	// 探索範囲がかかるすべてのセルからアクター情報を収集
	for (int ix = cx1 ; ix <= cx2 ; ix++) {
		for (int iy = cy1 ; iy <= cy2 ; iy++) {
			int cellpos = iy * m_gridcount.x + ix;
			if (cellpos < 0 || cellpos >= m_grid.size()) continue;
			CollisionGridItemVec & cell = m_grid[cellpos];
			
			for (CollisionGridItemVec::iterator it = cell.begin(); it != cell.end() ; it++) {
				CollisionGridItem &item = *it;
				if (! check_collision || is_intersect_rects(x,y,w,h, item.x,item.y,item.w,item.h)) {
					m_results.push_back(item.id);
				}
			}
		}
	}

	std::sort(m_results.begin(), m_results.end());
	std::vector<int>::iterator new_end = std::unique(m_results.begin(), m_results.end());
	m_results.erase(new_end, m_results.end());

	return m_results.size();

}

// グリッド内のデータをすべて空にして、init後の状態まで戻す。
void CollisionDetector::clear()
{
	for ( CollisionGridItemVecVec::iterator it = m_grid.begin() ; it != m_grid.end() ; it++ ) {
		CollisionGridItemVec & cell = *it;
		cell.clear();
	}
}
