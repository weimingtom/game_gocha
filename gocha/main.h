#ifndef _MAIN_H_
#define _MAIN_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_opengl.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GameCommon.h"
#include "SpriteNode.h"
#include "LuaHelper.h"

#include "resource.h"

extern DrawSystem *GetDrawSystem();
extern ImageLoader *GetImageLoader();
extern TTF_Font *GetFont();
extern void GetMousePos(int *x, int *y);
extern void ReloadLuaFiles(const char* arg);
extern bool DoLuaFile(const char* path);
extern void WaitInputOnError(const char *mes, const char *postfix);
extern const char * GetLuaError();
extern void RequestQuit();

#endif // _MAIN_H_
