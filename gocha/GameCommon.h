#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

// 次のフレームまで待つ関数
extern void WaitNextFrame();

// フレームレートを得る
extern float GetFPS();

// デバッグ用文字出力
extern void DebugPrint(const char *str);

// デバッグ用文字出力 printf風
extern void DebugPrintf(const char* format, ...);

// デバッグ用文字出力 printf風 改行つき
extern void DebugPrintfLn(const char* format, ...);


// lowからhighまでのランダム値を取得（整数）
inline int RandomInt(int low, int high) {
	return (rand() * (high-low) / RAND_MAX) + low;
}

// lowからhighまでのランダム値を取得（浮動小数点数）
inline float RandomFloat(float low, float high) {
	return ((float)rand() * (high-low) / (float)RAND_MAX) + low;
}

#endif // __GAME_COMMON_H__