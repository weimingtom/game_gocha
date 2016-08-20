#ifndef _COLLISION_H_
#define _COLLISION_H_

class Point
{
public:
	int x;
	int y;
	Point(int _x = 0, int _y = 0) 
		: x(_x), y(_y) {}
	void Set(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

class CollisionGridItem
{
public:
	int id;
	int x,y,w,h;
	CollisionGridItem(int _id, int _x, int _y, int _w, int _h) 
		: id(_id), x(_x), y(_y), w(_w), h(_h) {}
	void SetRect(int _x, int _y, int _w, int _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};

typedef std::vector< CollisionGridItem > CollisionGridItemVec;
typedef std::vector< CollisionGridItemVec > CollisionGridItemVecVec;

class CollisionDetector { //tolua_export
private:
	CollisionGridItemVecVec m_grid;
	Point m_gridspan;
	Point m_fieldsize;
	Point m_gridcount;
	std::vector< int > m_results;

public :
	// tolua_begin

	CollisionDetector() {}
	~CollisionDetector() {}

	void init(int fieldsize_x, int fieldsize_y, int gridspan_x, int gridspan_y);
	void add_object(int id, int x, int y, int w, int h);
	int search_collided_objects(int x, int y, int w, int h) {
		return search_near_objects(x,y,w,h,true);
	}
	int search_near_objects(int x, int y, int w, int h, bool check_collision);
	void clear();

	int get_result(int index) {
		return m_results[index];
	}
};
// tolua_end


#endif // _COLLISION_H_
