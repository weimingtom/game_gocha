#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "GameCommon.h"
#include "SDL.h"


// デバッグ出力
void DebugPrint(const char *str) {
#ifdef _WIN32
	// VC++のメッセージとして出力
	OutputDebugString(str);
#else
	fprintf(stderr, str);
#endif
}

// デバッグ用文字出力 printf風
void DebugPrintf(const char* format, ...) {
	va_list vl;
	va_start(vl,format);
	static char tmp[10000];
	vsprintf(tmp, format,vl);
	DebugPrint(tmp);
	va_end(vl);
}

// デバッグ用文字出力 printf風 改行つき
void DebugPrintfLn(const char* format, ...) {
	va_list vl;
	va_start(vl,format);
	static char tmp[10000];
	vsprintf(tmp, format,vl);
	strcat(tmp, "\n");
	DebugPrint(tmp);
	va_end(vl);
}


// フレームレート計算用
static unsigned int s_prevframe = 0;
//static const int s_target_fps = 1000;//60;
static const int s_target_fps = 60;
static const int s_target_frame_millisec = 1000 / s_target_fps;

static bool s_bKeepFrameRate = true; // フレームレートを維持するかどうかのフラグ

// フレーム時間記録バッファ（FPS計測用）
#define FRAME_TIMES_COUNT 50
static unsigned int s_frametimes[FRAME_TIMES_COUNT];

// 次のフレームまで待つ関数
// 指定FPSに対して時間が早すぎるようならば少しウエイトする
void WaitNextFrame()
{
	unsigned int current = SDL_GetTicks();
	if (s_bKeepFrameRate) {
		while (current < s_prevframe + s_target_frame_millisec) {
			if ( s_prevframe + s_target_frame_millisec - current <= 1) {
				// あと1ms以下ならループで時間調整（Delayすると時間を過ぎるため）
				current = SDL_GetTicks();
				continue;
			}
			SDL_Delay(1);
			current = SDL_GetTicks();
		}
	}
	s_prevframe = current;

	// FPS計測用
	for (int i=FRAME_TIMES_COUNT-1 ; i>=1 ; i--) {
		s_frametimes[i] = s_frametimes[i-1];
	}
	s_frametimes[0] = current;
}

// フレームレートを得る
float GetFPS()
{
	unsigned int diff = s_frametimes[0] - s_frametimes[FRAME_TIMES_COUNT-1];
	if (diff == 0) return 0;
	return 1000.0f / ((float)diff / (float)(FRAME_TIMES_COUNT-1));
}