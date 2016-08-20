// toluatest1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <locale.h>
#include <string>

#if defined(_WIN32) && !defined(__MINGW32__) // Windows用のみ
#include <crtdbg.h>
#include "SDL_syswm.h"
#endif

#include "main.h"

#include "lua.hpp"
#include "tolua++.h"
#include "tolua_bind\luafunc_glue.h"


ImageLoader g_imageloader; // 画像ローダー
DrawSystem g_drawsystem;   // スプライト描画システム
TTF_Font *g_font = NULL;   // フォント

lua_State *g_L = NULL;
LuaHelper g_luah;

// SDL画面オブジェクト
SDL_Surface *g_screen = NULL;

// フレームレート表示用スプライト
SpriteNode g_fpstext;

// ゲーム終了要求フラグ
bool g_request_quit = false;

// Lua用にアクセス関数を用意しておく

DrawSystem *GetDrawSystem()
{
	return &g_drawsystem;
}
ImageLoader *GetImageLoader()
{
	return &g_imageloader;
}
TTF_Font *GetFont()
{
	return g_font;
}
// マウスの状態をLuaから取得するための関数
void GetMousePos(int *x = NULL, int *y = NULL) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (x) *x = mouse_x;
	if (y) *y = mouse_y;
}

// ゲーム終了を要求する
void RequestQuit()
{
	g_request_quit = true;
}

/*
// 新しい最小のユーザーデータを作成して返す
// 引数で受け取ったテーブルをメタテーブルにセットする。
int GetNewUserData(lua_State *L)
{
	lua_settop(L, 0);
	lua_newuserdata(L, 0);
	lua_newtable(L);
	lua_setmetatable(L, -2);
	return 1;
}
*/


// エラー時の入力待ち関数
void WaitInputOnError(const char *mes, const char *postfix)
{
#ifdef _WIN32
	char text[1000];
	strcpy(text, mes);
	strcat(text, ".\r\n");
	strcat(text, postfix);
	DebugPrintfLn(mes);
	MessageBox(NULL, text, "Error", MB_OK);
#else
	char text[1000];
	strcpy(text, mes);
	strcat(text, ".\n ");
	strcat(text, postfix);
	strcat(text, "\n>");
	printf(text);
	getchar();
#endif
}

// エラーがなくなるまでリロードを繰り返す
void ReloadLuaFiles(const char* arg = "") {
	LuaFuncParam param;
	param.String(arg);
	LuaFuncParam result;
	while (true) {
		if (g_luah.DoFile("scripts_game/reload.lua", &result, 2, &param)) {
			if (result.GetBool(0)) {
				// スクリプトリロード成功
				break;
			}
			WaitInputOnError(result.GetString(1), "Reload OK?");
		}
		else {
			WaitInputOnError(g_luah.GetErr(), "Reload OK?");
		}
	}
}

// Luaファイルを実行
bool DoLuaFile(const char* path) {
	std::string err;
	if (!g_luah.DoFile(path, NULL, 0, NULL)) {
		// エラー文字列を返す
		err = g_luah.GetErr();
		DebugPrintfLn("DoLuaFile: %s", err.c_str());
		return false;
	}
	return true;
}

// Luaのエラーを取得する
const char * GetLuaError() {
	return g_luah.GetErr();
}


// OpenGLをスプライト描画向けに初期化
void InitOpenGL(int width, int height)
{
	// テクスチャ関連設定
	glEnable(GL_TEXTURE_2D);
	glShadeModel( GL_FLAT );

	// カリングなし
	glDisable( GL_CULL_FACE );

	// 背景色設定
	glClearColor( 0, 0, 0, 0 );

	// 2D的な座標系設定
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D( 0.0, width, height, 0.0 );

	// ピクセル計算?アルファブレンド
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE); // 加算の場合
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

// Luaを初期化
void InitLua()
{
	// Luaステートを生成
	g_L = lua_open();
    if ( !g_L ) {
        fprintf(stderr, "Unable to init Lua\n");
        exit(1);
    }

	// 標準ライブラリをロードする
	luaL_openlibs(g_L);

	// ユーザーデータ作成関数のみ登録
	//lua_register(g_L, "GetNewUserData", GetNewUserData);

	// Luaヘルパーにセット
	g_luah.SetLua(g_L);

	// print関数を設定
	g_luah.InitPrintFunc();

	// toluaでCの関数やクラスをインポート
	tolua_luafunc_open(g_L);

}

// Luaを初期化
void EndLua()
{
}

// SDLの終了処理
void EndSDL()
{
	TTF_CloseFont(g_font);
	TTF_Quit();

	SDL_Quit();
}

// SDL初期化
void InitSDL()
{
#ifdef __linux__
	putenv("SDL_VIDEODRIVER=dga");
#elif defined(_WIN32) 
	//_putenv("SDL_VIDEODRIVER=directx");
#endif

    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
        DebugPrintfLn("Unable to init SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    //SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// フォント表示ライブラリ SDL_ttf の初期化
	if (TTF_Init() == -1) {
        DebugPrintfLn("Unable to init SDL_ttf: %s", TTF_GetError());
        exit(1);
	}
	// IPAゴシックフォントを使用
	g_font = TTF_OpenFont("ipafont/ipag.ttf", 16);
	if (!g_font) {
        DebugPrintfLn("Unable to Load Font: %s", TTF_GetError());
        exit(1);
	}

	unsigned int flags = SDL_OPENGL;
	//unsigned int flags = SDL_HWSURFACE | SDL_OPENGL;
	//flags |= SDL_FULLSCREEN;
    g_screen = SDL_SetVideoMode(640, 480, 0, flags);
    if ( g_screen == NULL ) {
        DebugPrintfLn("Unable to set 640x480 video: %s", SDL_GetError());
        exit(1);
    }

	// OpenGLをスプライト描画用に初期化
	InitOpenGL(g_screen->w, g_screen->h);

	g_drawsystem.SetScreenSize(g_screen->w, g_screen->h);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE); // Window Message取得（サスペンド阻止用）
}

//#define MAX_LOADSTRING 100


void InitGame()
{
	// スプライト画像の追加
	if (!g_imageloader.AddSurface("frame", IMG_Load("frame.png"), 64,64,8)) {
		exit(1);
	}

	g_fpstext.SetFont(g_font);
	g_fpstext.SetText("プログラムサンプル");
	g_fpstext.MoveTo(250,10);
	g_fpstext.SetZ(10000);
	g_fpstext.SetScale(1.0,1.0);

	g_drawsystem.AddNode(&g_fpstext);

	// 初期化スクリプトを呼ぶ
	/*
	if (
		//!g_luah.DoFile("scripts_common/debugger.lua")
		 !g_luah.DoFile("scripts_common/explicit_globals.lua")
		|| !g_luah.DoFile("scripts_common/common.lua")
		|| !g_luah.DoFile("scripts_common/class.lua")
		//|| !g_luah.DoFile("scripts_common/test_class.lua")
		//|| !g_luah.DoFile("scripts_common/system.lua")
		|| !g_luah.DoFile("scripts_common/coroutine.lua")
		|| !g_luah.DoFile("scripts_common/collision.lua")
		|| !g_luah.DoFile("scripts_common/actor.lua")
		|| !g_luah.DoFile("scripts_game/gameinit.lua")
		|| !g_luah.DoFile("scripts_game/gamefield.lua")
		|| !g_luah.DoFile("scripts_game/gamechars.lua")
		|| !g_luah.DoFile("scripts_game/gamechars_enemy.lua")
		|| !g_luah.DoFile("scripts_game/gametitle.lua")) {
		WaitInputOnError(g_luah.GetErr(), "Exit OK?");
		exit(1);
	}
	*/

	// リロードと初期ロードをまとめる
	if (!g_luah.DoFile("scripts_common/explicit_globals.lua")) {
		WaitInputOnError(g_luah.GetErr(), "Exit OK?");
		exit(1);
	}
	ReloadLuaFiles("load");

	// 初期化用Lua関数を呼ぶ
	LuaFuncParam result;
	if (!g_luah.CallFunc("startfunc", &result, 1)) {
		WaitInputOnError(g_luah.GetErr(), "Exit OK?");
		exit(1);
	}
	else {
		// 関数の返り値
		const char *str = result.GetString(0);
	}
}

void EndGame()
{
	g_fpstext.Destroy();

	// 終了処理
	g_imageloader.Destroy();
}

// １フレーム処理を進める
void ProcessFrame()
{
	// FPSおよびレンダラー表示
	static int fpscount = 0;
	if (++fpscount > 30) {
		char fpsstr[500];
		int script_memory_size = lua_gc(g_luah.GetLua(),LUA_GCCOUNT,0);
		const char *renderer_name = (const char *) glGetString(GL_RENDERER);
		sprintf(fpsstr, "%3.1ffps %4dKB %s", GetFPS(), script_memory_size, renderer_name);
		g_fpstext.SetText(fpsstr);
		fpscount = 0;
	}

	// フレーム関数を呼ぶ（失敗したらリロードして再度チャレンジ）
	LuaFuncParam result;
	while (!g_luah.CallFunc("framefunc", &result, 1)) {
		WaitInputOnError(g_luah.GetErr(), "Reload OK?");
		ReloadLuaFiles("all");
	}
	const char *str = result.GetString(0);
}

// １フレーム描画
void DrawFrame()
{
	// 画面クリア
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// 座標変換を「なし」にする
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// キャラクター（背景や文字も含む）描画
	g_drawsystem.DrawGL();
	glFlush();
}

void HandleEvents(SDL_Event &event)
{
	switch( event.type ) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		{
			bool is_down = (event.type == SDL_KEYDOWN);
			// フルスクリーン切り替え（可能な場合のみ）
			if (event.key.keysym.sym == SDLK_RETURN && (SDL_GetModState() & KMOD_ALT)) {
				if (!SDL_WM_ToggleFullScreen(g_screen)) {
					DebugPrintfLn("Toggle Fullscreen Failed");
				}
			}
			// ESCキー→ゲーム終了
			else if (event.key.keysym.sym == SDLK_ESCAPE) {
				g_request_quit = true;
			}
			// Luaにキー押下情報を渡す
			{
				// on_keyevent(key, is_down, is_ctrl, is_alt, is_shift) という関数を呼ぶ
				LuaFuncParam params;
				params.Number(event.key.keysym.sym)
					.Bool(is_down)
					.Bool((SDL_GetModState() & KMOD_CTRL) != 0)
					.Bool((SDL_GetModState() & KMOD_ALT) != 0)
					.Bool((SDL_GetModState() & KMOD_SHIFT) != 0);
				if (!g_luah.CallFunc("on_keyevent", NULL, 0, &params)) {
					WaitInputOnError(g_luah.GetErr(), "Continue OK?");
				}
			}
		}
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		{
			// Luaにマウスクリック情報を渡す
			char *evtype = "";
			int button = 0;

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				evtype = "down";
				button = event.button.button;
			}
			else if (event.type == SDL_MOUSEBUTTONUP) {
				evtype = "up";
				button = event.button.button;
			}
			else {
				evtype = "move";
			}
			// on_mousedown(button, x, y) という関数を呼ぶ
			LuaFuncParam params;
			params.String(evtype)
				.Number(button)
				.Number(event.button.x)
				.Number(event.button.y);
			if (!g_luah.CallFunc("on_mouseevent", NULL, 0, &params)) {
				WaitInputOnError(g_luah.GetErr(), "Continue OK?");
			}
		}
		break;
	case SDL_QUIT:
		g_request_quit = true;
		break;

#if defined(_WIN32) && !defined(__MINGW32__)
	case SDL_SYSWMEVENT:
		if (event.syswm.msg->msg == WM_POWERBROADCAST) {
			SDL_SysWMEvent *wm = &event.syswm;
			SDL_SysWMmsg *msg = wm->msg;			
			if (msg->wParam == PBT_APMQUERYSUSPEND) {
				// サスペンドのクエリきたら終了！（OpenGLがおかしくなるマシンがあるため）
				g_request_quit = true;
			}
		}
		break;
#endif
	}
}


#ifdef _WIN32
// Windowsの場合のエントリポイント
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	return main(__argc, __argv);
}
#endif

// メイン関数
int main(int argc, char **argv)
{
	// TTF日本語表示に必要
	setlocale(LC_ALL, "Japanese");

#if defined(_WIN32) && !defined(__MINGW32__)
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// スクリプトの初期化
	InitLua();

	// グラフィックの初期化
	InitSDL();

	// ゲームの初期化
	InitGame();

	// メインループ
	while( !g_request_quit ) {
		// イベント処理
		SDL_Event event;
		while( SDL_PollEvent( &event ) ) {
			HandleEvents(event);
		}
		// １フレーム処理を進める
		ProcessFrame();
		// 画面描画
		DrawFrame();
		// 次フレームまで時間待ち、FPS計測
		WaitNextFrame();
		// フレーム切り替え
		SDL_GL_SwapBuffers();
	}

	// ゲームの終了処理
	EndGame();

	// SDLの終了処理
	EndSDL();

	return 0;
}

