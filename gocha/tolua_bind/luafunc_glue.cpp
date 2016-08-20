/*
** Lua binding: luafunc
** Generated automatically by tolua++-1.0.92 on 01/30/14 09:56:10.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_luafunc_open (lua_State* tolua_S);

#include "..\stdafx.h"
#include "..\SpriteNode.h"
#include "..\LuaHelper.h"
#include <vector>
#include "..\Collision.h"
#include <string>
#include "..\Collision.h"
#include "../main.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CollisionDetector (lua_State* tolua_S)
{
 CollisionDetector* self = (CollisionDetector*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_SpriteNode (lua_State* tolua_S)
{
 SpriteNode* self = (SpriteNode*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_DrawSystem (lua_State* tolua_S)
{
 DrawSystem* self = (DrawSystem*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_GLuint (lua_State* tolua_S)
{
 GLuint* self = (GLuint*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_ImageLoader (lua_State* tolua_S)
{
 ImageLoader* self = (ImageLoader*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CollisionDetector");
 tolua_usertype(tolua_S,"DrawSystem");
 tolua_usertype(tolua_S,"SpriteNode");
 tolua_usertype(tolua_S,"SDL_Surface");
 tolua_usertype(tolua_S,"GLuint");
 tolua_usertype(tolua_S,"TTF_Font");
 tolua_usertype(tolua_S,"ImageLoader");
 tolua_usertype(tolua_S,"ImageLoaderItem");
}

/* method: new of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_new00
static int tolua_luafunc_cclass_ImageLoader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageLoader* tolua_ret = (ImageLoader*)  new ImageLoader();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ImageLoader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_new00_local
static int tolua_luafunc_cclass_ImageLoader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageLoader* tolua_ret = (ImageLoader*)  new ImageLoader();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"ImageLoader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_delete00
static int tolua_luafunc_cclass_ImageLoader_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageLoader* self = (ImageLoader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_Destroy00
static int tolua_luafunc_cclass_ImageLoader_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageLoader* self = (ImageLoader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'",NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSurface of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_AddSurface00
static int tolua_luafunc_cclass_ImageLoader_AddSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"SDL_Surface",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageLoader* self = (ImageLoader*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  SDL_Surface* surface = ((SDL_Surface*)  tolua_tousertype(tolua_S,3,0));
  int xgridspan = ((int)  tolua_tonumber(tolua_S,4,0));
  int ygridspan = ((int)  tolua_tonumber(tolua_S,5,0));
  int xgridcount = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSurface'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddSurface(name,surface,xgridspan,ygridspan,xgridcount);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSurface'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSurfaceByFileName of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_AddSurfaceByFileName00
static int tolua_luafunc_cclass_ImageLoader_AddSurfaceByFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageLoader* self = (ImageLoader*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filename = ((const char*)  tolua_tostring(tolua_S,3,0));
  int xgridspan = ((int)  tolua_tonumber(tolua_S,4,0));
  int ygridspan = ((int)  tolua_tonumber(tolua_S,5,0));
  int xgridcount = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSurfaceByFileName'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddSurfaceByFileName(name,filename,xgridspan,ygridspan,xgridcount);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSurfaceByFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItemByName of class  ImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_ImageLoader_GetItemByName00
static int tolua_luafunc_cclass_ImageLoader_GetItemByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ImageLoader",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ImageLoader* self = (ImageLoader*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItemByName'",NULL);
#endif
  {
   ImageLoaderItem* tolua_ret = (ImageLoaderItem*)  self->GetItemByName(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ImageLoaderItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItemByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_new00
static int tolua_luafunc_cclass_SpriteNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteNode* tolua_ret = (SpriteNode*)  new SpriteNode();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_new00_local
static int tolua_luafunc_cclass_SpriteNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SpriteNode* tolua_ret = (SpriteNode*)  new SpriteNode();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"SpriteNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_delete00
static int tolua_luafunc_cclass_SpriteNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_Destroy00
static int tolua_luafunc_cclass_SpriteNode_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'",NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetImageLoader of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetImageLoader00
static int tolua_luafunc_cclass_SpriteNode_SetImageLoader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  ImageLoader* loader = ((ImageLoader*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetImageLoader'",NULL);
#endif
  {
   self->SetImageLoader(loader);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetImageLoader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetImageName of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetImageName00
static int tolua_luafunc_cclass_SpriteNode_GetImageName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetImageName'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetImageName();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetParent00
static int tolua_luafunc_cclass_SpriteNode_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'",NULL);
#endif
  {
   SpriteNode* tolua_ret = (SpriteNode*)  self->GetParent();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Show of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_Show00
static int tolua_luafunc_cclass_SpriteNode_Show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  bool show = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Show'",NULL);
#endif
  {
   self->Show(show);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Show'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOpType of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetOpType00
static int tolua_luafunc_cclass_SpriteNode_SetOpType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  SpriteNode::ENUM_OP_TYPE op_type = ((SpriteNode::ENUM_OP_TYPE) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOpType'",NULL);
#endif
  {
   self->SetOpType(op_type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOpType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MoveTo of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_MoveTo00
static int tolua_luafunc_cclass_SpriteNode_MoveTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MoveTo'",NULL);
#endif
  {
   self->MoveTo(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoveTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Offset of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_Offset00
static int tolua_luafunc_cclass_SpriteNode_Offset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Offset'",NULL);
#endif
  {
   self->Offset(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Offset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetX of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetX00
static int tolua_luafunc_cclass_SpriteNode_GetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetX'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetX of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetX00
static int tolua_luafunc_cclass_SpriteNode_SetX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetX'",NULL);
#endif
  {
   self->SetX(x);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetY of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetY00
static int tolua_luafunc_cclass_SpriteNode_GetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetY'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetY of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetY00
static int tolua_luafunc_cclass_SpriteNode_SetY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int y = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetY'",NULL);
#endif
  {
   self->SetY(y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZ of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetZ00
static int tolua_luafunc_cclass_SpriteNode_GetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZ'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZ of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetZ00
static int tolua_luafunc_cclass_SpriteNode_SetZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int z = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZ'",NULL);
#endif
  {
   self->SetZ(z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCenter of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetCenter00
static int tolua_luafunc_cclass_SpriteNode_SetCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCenter'",NULL);
#endif
  {
   self->SetCenter(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetScale00
static int tolua_luafunc_cclass_SpriteNode_SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'",NULL);
#endif
  {
   self->SetScale(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetColor00
static int tolua_luafunc_cclass_SpriteNode_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
  float g = ((float)  tolua_tonumber(tolua_S,3,0));
  float b = ((float)  tolua_tonumber(tolua_S,4,0));
  float a = ((float)  tolua_tonumber(tolua_S,5,1.0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'",NULL);
#endif
  {
   self->SetColor(r,g,b,a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlpha of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetAlpha00
static int tolua_luafunc_cclass_SpriteNode_SetAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float alpha = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlpha'",NULL);
#endif
  {
   self->SetAlpha(alpha);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TranslateParentToThis of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_TranslateParentToThis00
static int tolua_luafunc_cclass_SpriteNode_TranslateParentToThis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  bool use_this_scale = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TranslateParentToThis'",NULL);
#endif
  {
   self->TranslateParentToThis(&x,&y,use_this_scale);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TranslateParentToThis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TranslateThisToParent of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_TranslateThisToParent00
static int tolua_luafunc_cclass_SpriteNode_TranslateThisToParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  bool use_this_scale = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TranslateThisToParent'",NULL);
#endif
  {
   self->TranslateThisToParent(&x,&y,use_this_scale);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TranslateThisToParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TranslateRootToThis of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_TranslateRootToThis00
static int tolua_luafunc_cclass_SpriteNode_TranslateRootToThis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  bool use_this_scale = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TranslateRootToThis'",NULL);
#endif
  {
   self->TranslateRootToThis(&x,&y,use_this_scale);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TranslateRootToThis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TranslateThisToRoot of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_TranslateThisToRoot00
static int tolua_luafunc_cclass_SpriteNode_TranslateThisToRoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  bool use_this_scale = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TranslateThisToRoot'",NULL);
#endif
  {
   self->TranslateThisToRoot(&x,&y,use_this_scale);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TranslateThisToRoot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChipGrid of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetChipGrid00
static int tolua_luafunc_cclass_SpriteNode_SetChipGrid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int xspan = ((int)  tolua_tonumber(tolua_S,2,0));
  int yspan = ((int)  tolua_tonumber(tolua_S,3,0));
  int xcount = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChipGrid'",NULL);
#endif
  {
   self->SetChipGrid(xspan,yspan,xcount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChipGrid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChipIndex of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetChipIndex00
static int tolua_luafunc_cclass_SpriteNode_SetChipIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChipIndex'",NULL);
#endif
  {
   self->SetChipIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChipIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChipSpan of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetChipSpan00
static int tolua_luafunc_cclass_SpriteNode_SetChipSpan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int x_chipspan = ((int)  tolua_tonumber(tolua_S,2,0));
  int y_chipspan = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChipSpan'",NULL);
#endif
  {
   self->SetChipSpan(x_chipspan,y_chipspan);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChipSpan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexture of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetTexture00
static int tolua_luafunc_cclass_SpriteNode_GetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexture'",NULL);
#endif
  {
   GLuint tolua_ret = (GLuint)  self->GetTexture();
   {
#ifdef __cplusplus
    void* tolua_obj = new GLuint(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GLuint");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLuint));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"GLuint");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetImageName of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetImageName00
static int tolua_luafunc_cclass_SpriteNode_SetImageName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"ImageLoader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  ImageLoader* loader = ((ImageLoader*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetImageName'",NULL);
#endif
  {
   self->SetImageName(name,loader);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetImageName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FetchImage of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_FetchImage00
static int tolua_luafunc_cclass_SpriteNode_FetchImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FetchImage'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->FetchImage();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FetchImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DrawGL of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_DrawGL00
static int tolua_luafunc_cclass_SpriteNode_DrawGL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DrawSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  DrawSystem* ds = ((DrawSystem*)  tolua_tousertype(tolua_S,2,0));
  float xbase = ((float)  tolua_tonumber(tolua_S,3,0));
  float ybase = ((float)  tolua_tonumber(tolua_S,4,0));
  float xbasescale = ((float)  tolua_tonumber(tolua_S,5,0));
  float ybasescale = ((float)  tolua_tonumber(tolua_S,6,0));
  int level = ((int)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DrawGL'",NULL);
#endif
  {
   self->DrawGL(ds,xbase,ybase,xbasescale,ybasescale,level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DrawGL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChildCount of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetChildCount00
static int tolua_luafunc_cclass_SpriteNode_GetChildCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SpriteNode* self = (const SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChildCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetChildCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChildCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChildAt of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_GetChildAt00
static int tolua_luafunc_cclass_SpriteNode_GetChildAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChildAt'",NULL);
#endif
  {
   SpriteNode* tolua_ret = (SpriteNode*)  self->GetChildAt(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"SpriteNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChildAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddChild of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_AddChild00
static int tolua_luafunc_cclass_SpriteNode_AddChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  SpriteNode* chr = ((SpriteNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddChild'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddChild(chr);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_RemoveChild00
static int tolua_luafunc_cclass_SpriteNode_RemoveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  SpriteNode* chr = ((SpriteNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveChild(chr);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveFromParent of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_RemoveFromParent00
static int tolua_luafunc_cclass_SpriteNode_RemoveFromParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveFromParent'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveFromParent();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveFromParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetFont00
static int tolua_luafunc_cclass_SpriteNode_SetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"TTF_Font",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  TTF_Font* font = ((TTF_Font*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'",NULL);
#endif
  {
   self->SetFont(font);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetText00
static int tolua_luafunc_cclass_SpriteNode_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'",NULL);
#endif
  {
   self->SetText(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextColor of class  SpriteNode */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_SpriteNode_SetTextColor00
static int tolua_luafunc_cclass_SpriteNode_SetTextColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SpriteNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SpriteNode* self = (SpriteNode*)  tolua_tousertype(tolua_S,1,0);
  unsigned int r = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int g = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int b = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextColor'",NULL);
#endif
  {
   self->SetTextColor(r,g,b);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_new00
static int tolua_luafunc_cclass_DrawSystem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DrawSystem* tolua_ret = (DrawSystem*)  new DrawSystem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"DrawSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_new00_local
static int tolua_luafunc_cclass_DrawSystem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DrawSystem* tolua_ret = (DrawSystem*)  new DrawSystem();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"DrawSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_delete00
static int tolua_luafunc_cclass_DrawSystem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DrawSystem* self = (DrawSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNode of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_AddNode00
static int tolua_luafunc_cclass_DrawSystem_AddNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DrawSystem* self = (DrawSystem*)  tolua_tousertype(tolua_S,1,0);
  SpriteNode* chr = ((SpriteNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNode'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddNode(chr);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveNode of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_RemoveNode00
static int tolua_luafunc_cclass_DrawSystem_RemoveNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SpriteNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DrawSystem* self = (DrawSystem*)  tolua_tousertype(tolua_S,1,0);
  SpriteNode* chr = ((SpriteNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveNode'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveNode(chr);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DrawGL of class  DrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_DrawSystem_DrawGL00
static int tolua_luafunc_cclass_DrawSystem_DrawGL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DrawSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DrawSystem* self = (DrawSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DrawGL'",NULL);
#endif
  {
   self->DrawGL();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DrawGL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_new00
static int tolua_luafunc_cclass_CollisionDetector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CollisionDetector* tolua_ret = (CollisionDetector*)  new CollisionDetector();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"CollisionDetector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_new00_local
static int tolua_luafunc_cclass_CollisionDetector_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CollisionDetector* tolua_ret = (CollisionDetector*)  new CollisionDetector();
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"CollisionDetector");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_delete00
static int tolua_luafunc_cclass_CollisionDetector_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_init00
static int tolua_luafunc_cclass_CollisionDetector_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
  int fieldsize_x = ((int)  tolua_tonumber(tolua_S,2,0));
  int fieldsize_y = ((int)  tolua_tonumber(tolua_S,3,0));
  int gridspan_x = ((int)  tolua_tonumber(tolua_S,4,0));
  int gridspan_y = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'",NULL);
#endif
  {
   self->init(fieldsize_x,fieldsize_y,gridspan_x,gridspan_y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: add_object of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_add_object00
static int tolua_luafunc_cclass_CollisionDetector_add_object00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int w = ((int)  tolua_tonumber(tolua_S,5,0));
  int h = ((int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'add_object'",NULL);
#endif
  {
   self->add_object(id,x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'add_object'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: search_collided_objects of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_search_collided_objects00
static int tolua_luafunc_cclass_CollisionDetector_search_collided_objects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int w = ((int)  tolua_tonumber(tolua_S,4,0));
  int h = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'search_collided_objects'",NULL);
#endif
  {
   int tolua_ret = (int)  self->search_collided_objects(x,y,w,h);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'search_collided_objects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: search_near_objects of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_search_near_objects00
static int tolua_luafunc_cclass_CollisionDetector_search_near_objects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int w = ((int)  tolua_tonumber(tolua_S,4,0));
  int h = ((int)  tolua_tonumber(tolua_S,5,0));
  bool check_collision = ((bool)  tolua_toboolean(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'search_near_objects'",NULL);
#endif
  {
   int tolua_ret = (int)  self->search_near_objects(x,y,w,h,check_collision);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'search_near_objects'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_clear00
static int tolua_luafunc_cclass_CollisionDetector_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'",NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: get_result of class  CollisionDetector */
#ifndef TOLUA_DISABLE_tolua_luafunc_cclass_CollisionDetector_get_result00
static int tolua_luafunc_cclass_CollisionDetector_get_result00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionDetector",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionDetector* self = (CollisionDetector*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get_result'",NULL);
#endif
  {
   int tolua_ret = (int)  self->get_result(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get_result'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetDrawSystem */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetDrawSystem00
static int tolua_luafunc_cfunc_GetDrawSystem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DrawSystem* tolua_ret = (DrawSystem*)  GetDrawSystem();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"DrawSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawSystem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetImageLoader */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetImageLoader00
static int tolua_luafunc_cfunc_GetImageLoader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ImageLoader* tolua_ret = (ImageLoader*)  GetImageLoader();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"ImageLoader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageLoader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetFont */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetFont00
static int tolua_luafunc_cfunc_GetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TTF_Font* tolua_ret = (TTF_Font*)  GetFont();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"TTF_Font");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetMousePos */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetMousePos00
static int tolua_luafunc_cfunc_GetMousePos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,1,NULL));
  int y = ((int)  tolua_tonumber(tolua_S,2,NULL));
  {
   GetMousePos(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMousePos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReloadLuaFiles */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_ReloadLuaFiles00
static int tolua_luafunc_cfunc_ReloadLuaFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* arg = ((const char*)  tolua_tostring(tolua_S,1,""));
  {
   ReloadLuaFiles(arg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReloadLuaFiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DoLuaFile */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_DoLuaFile00
static int tolua_luafunc_cfunc_DoLuaFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  DoLuaFile(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DoLuaFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: WaitInputOnError */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_WaitInputOnError00
static int tolua_luafunc_cfunc_WaitInputOnError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* mes = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* postfix = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   WaitInputOnError(mes,postfix);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'WaitInputOnError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetLuaError */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_GetLuaError00
static int tolua_luafunc_cfunc_GetLuaError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   const char* tolua_ret = (const char*)  GetLuaError();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestQuit */
#ifndef TOLUA_DISABLE_tolua_luafunc_cfunc_RequestQuit00
static int tolua_luafunc_cfunc_RequestQuit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RequestQuit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestQuit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SDL_Delay */
#ifndef TOLUA_DISABLE_tolua_luafunc_SDL_SDL_Delay00
static int tolua_luafunc_SDL_SDL_Delay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int ms = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  {
   SDL_Delay(ms);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SDL_Delay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_luafunc_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"SDLK_UNKNOWN",SDLK_UNKNOWN);
  tolua_constant(tolua_S,"SDLK_TAB",SDLK_TAB);
  tolua_constant(tolua_S,"SDLK_RETURN",SDLK_RETURN);
  tolua_constant(tolua_S,"SDLK_ESCAPE",SDLK_ESCAPE);
  tolua_constant(tolua_S,"SDLK_SPACE",SDLK_SPACE);
  tolua_constant(tolua_S,"SDLK_0",SDLK_0);
  tolua_constant(tolua_S,"SDLK_1",SDLK_1);
  tolua_constant(tolua_S,"SDLK_2",SDLK_2);
  tolua_constant(tolua_S,"SDLK_3",SDLK_3);
  tolua_constant(tolua_S,"SDLK_4",SDLK_4);
  tolua_constant(tolua_S,"SDLK_5",SDLK_5);
  tolua_constant(tolua_S,"SDLK_6",SDLK_6);
  tolua_constant(tolua_S,"SDLK_7",SDLK_7);
  tolua_constant(tolua_S,"SDLK_8",SDLK_8);
  tolua_constant(tolua_S,"SDLK_9",SDLK_9);
  tolua_constant(tolua_S,"SDLK_DELETE",SDLK_DELETE);
  tolua_constant(tolua_S,"SDLK_KP0",SDLK_KP0);
  tolua_constant(tolua_S,"SDLK_KP1",SDLK_KP1);
  tolua_constant(tolua_S,"SDLK_KP3",SDLK_KP3);
  tolua_constant(tolua_S,"SDLK_KP4",SDLK_KP4);
  tolua_constant(tolua_S,"SDLK_KP5",SDLK_KP5);
  tolua_constant(tolua_S,"SDLK_KP6",SDLK_KP6);
  tolua_constant(tolua_S,"SDLK_KP7",SDLK_KP7);
  tolua_constant(tolua_S,"SDLK_KP8",SDLK_KP8);
  tolua_constant(tolua_S,"SDLK_KP9",SDLK_KP9);
  tolua_constant(tolua_S,"SDLK_KP_PERIOD",SDLK_KP_PERIOD);
  tolua_constant(tolua_S,"SDLK_KP_DIVIDE",SDLK_KP_DIVIDE);
  tolua_constant(tolua_S,"SDLK_KP_MULTIPLY",SDLK_KP_MULTIPLY);
  tolua_constant(tolua_S,"SDLK_KP_MINUS",SDLK_KP_MINUS);
  tolua_constant(tolua_S,"SDLK_KP_PLUS",SDLK_KP_PLUS);
  tolua_constant(tolua_S,"SDLK_KP_ENTER",SDLK_KP_ENTER);
  tolua_constant(tolua_S,"SDLK_KP_EQUALS",SDLK_KP_EQUALS);
  tolua_constant(tolua_S,"SDLK_UP",SDLK_UP);
  tolua_constant(tolua_S,"SDLK_DOWN",SDLK_DOWN);
  tolua_constant(tolua_S,"SDLK_RIGHT",SDLK_RIGHT);
  tolua_constant(tolua_S,"SDLK_LEFT",SDLK_LEFT);
  tolua_constant(tolua_S,"SDLK_INSERT",SDLK_INSERT);
  tolua_constant(tolua_S,"SDLK_HOME",SDLK_HOME);
  tolua_constant(tolua_S,"SDLK_END",SDLK_END);
  tolua_constant(tolua_S,"SDLK_PAGEUP",SDLK_PAGEUP);
  tolua_constant(tolua_S,"SDLK_PAGEDOWN",SDLK_PAGEDOWN);
  tolua_constant(tolua_S,"SDLK_F1",SDLK_F1);
  tolua_constant(tolua_S,"SDLK_F2",SDLK_F2);
  tolua_constant(tolua_S,"SDLK_F3",SDLK_F3);
  tolua_constant(tolua_S,"SDLK_F4",SDLK_F4);
  tolua_constant(tolua_S,"SDLK_F5",SDLK_F5);
  tolua_constant(tolua_S,"SDLK_F6",SDLK_F6);
  tolua_constant(tolua_S,"SDLK_F7",SDLK_F7);
  tolua_constant(tolua_S,"SDLK_F8",SDLK_F8);
  tolua_constant(tolua_S,"SDLK_F9",SDLK_F9);
  tolua_constant(tolua_S,"SDLK_F10",SDLK_F10);
  tolua_constant(tolua_S,"SDLK_F11",SDLK_F11);
  tolua_constant(tolua_S,"SDLK_F12",SDLK_F12);
  tolua_constant(tolua_S,"SDLK_F13",SDLK_F13);
  tolua_constant(tolua_S,"SDLK_F14",SDLK_F14);
  tolua_constant(tolua_S,"SDLK_F15",SDLK_F15);
  tolua_constant(tolua_S,"SDLK_NUMLOCK",SDLK_NUMLOCK);
  tolua_constant(tolua_S,"SDLK_CAPSLOCK",SDLK_CAPSLOCK);
  tolua_constant(tolua_S,"SDLK_RSHIFT",SDLK_RSHIFT);
  tolua_constant(tolua_S,"SDLK_LSHIFT",SDLK_LSHIFT);
  tolua_constant(tolua_S,"SDLK_RCTRL",SDLK_RCTRL);
  tolua_constant(tolua_S,"SDLK_LCTRL",SDLK_LCTRL);
  tolua_constant(tolua_S,"SDLK_RALT",SDLK_RALT);
  tolua_constant(tolua_S,"SDLK_LALT",SDLK_LALT);
  tolua_constant(tolua_S,"KMOD_NONE",KMOD_NONE);
  tolua_constant(tolua_S,"KMOD_LSHIFT",KMOD_LSHIFT);
  tolua_constant(tolua_S,"KMOD_RSHIFT",KMOD_RSHIFT);
  tolua_constant(tolua_S,"KMOD_LCTRL",KMOD_LCTRL);
  tolua_constant(tolua_S,"KMOD_RCTRL",KMOD_RCTRL);
  tolua_constant(tolua_S,"KMOD_LALT",KMOD_LALT);
  tolua_constant(tolua_S,"KMOD_RALT",KMOD_RALT);
  tolua_constant(tolua_S,"KMOD_CAPS",KMOD_CAPS);
  tolua_constant(tolua_S,"KMOD_CTRL",KMOD_CTRL);
  tolua_constant(tolua_S,"KMOD_SHIFT",KMOD_SHIFT);
  tolua_constant(tolua_S,"KMOD_ALT",KMOD_ALT);
  tolua_module(tolua_S,"cclass",0);
  tolua_beginmodule(tolua_S,"cclass");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ImageLoader","ImageLoader","",tolua_collect_ImageLoader);
   #else
   tolua_cclass(tolua_S,"ImageLoader","ImageLoader","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ImageLoader");
    tolua_function(tolua_S,"new",tolua_luafunc_cclass_ImageLoader_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_cclass_ImageLoader_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_cclass_ImageLoader_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_cclass_ImageLoader_delete00);
    tolua_function(tolua_S,"Destroy",tolua_luafunc_cclass_ImageLoader_Destroy00);
    tolua_function(tolua_S,"AddSurface",tolua_luafunc_cclass_ImageLoader_AddSurface00);
    tolua_function(tolua_S,"AddSurfaceByFileName",tolua_luafunc_cclass_ImageLoader_AddSurfaceByFileName00);
    tolua_function(tolua_S,"GetItemByName",tolua_luafunc_cclass_ImageLoader_GetItemByName00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"SpriteNode","SpriteNode","",tolua_collect_SpriteNode);
   #else
   tolua_cclass(tolua_S,"SpriteNode","SpriteNode","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"SpriteNode");
    tolua_constant(tolua_S,"OP_NORMAL",SpriteNode::OP_NORMAL);
    tolua_constant(tolua_S,"OP_ADD",SpriteNode::OP_ADD);
    tolua_function(tolua_S,"new",tolua_luafunc_cclass_SpriteNode_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_cclass_SpriteNode_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_cclass_SpriteNode_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_cclass_SpriteNode_delete00);
    tolua_function(tolua_S,"Destroy",tolua_luafunc_cclass_SpriteNode_Destroy00);
    tolua_function(tolua_S,"SetImageLoader",tolua_luafunc_cclass_SpriteNode_SetImageLoader00);
    tolua_function(tolua_S,"GetImageName",tolua_luafunc_cclass_SpriteNode_GetImageName00);
    tolua_function(tolua_S,"GetParent",tolua_luafunc_cclass_SpriteNode_GetParent00);
    tolua_function(tolua_S,"Show",tolua_luafunc_cclass_SpriteNode_Show00);
    tolua_function(tolua_S,"SetOpType",tolua_luafunc_cclass_SpriteNode_SetOpType00);
    tolua_function(tolua_S,"MoveTo",tolua_luafunc_cclass_SpriteNode_MoveTo00);
    tolua_function(tolua_S,"Offset",tolua_luafunc_cclass_SpriteNode_Offset00);
    tolua_function(tolua_S,"GetX",tolua_luafunc_cclass_SpriteNode_GetX00);
    tolua_function(tolua_S,"SetX",tolua_luafunc_cclass_SpriteNode_SetX00);
    tolua_function(tolua_S,"GetY",tolua_luafunc_cclass_SpriteNode_GetY00);
    tolua_function(tolua_S,"SetY",tolua_luafunc_cclass_SpriteNode_SetY00);
    tolua_function(tolua_S,"GetZ",tolua_luafunc_cclass_SpriteNode_GetZ00);
    tolua_function(tolua_S,"SetZ",tolua_luafunc_cclass_SpriteNode_SetZ00);
    tolua_function(tolua_S,"SetCenter",tolua_luafunc_cclass_SpriteNode_SetCenter00);
    tolua_function(tolua_S,"SetScale",tolua_luafunc_cclass_SpriteNode_SetScale00);
    tolua_function(tolua_S,"SetColor",tolua_luafunc_cclass_SpriteNode_SetColor00);
    tolua_function(tolua_S,"SetAlpha",tolua_luafunc_cclass_SpriteNode_SetAlpha00);
    tolua_function(tolua_S,"TranslateParentToThis",tolua_luafunc_cclass_SpriteNode_TranslateParentToThis00);
    tolua_function(tolua_S,"TranslateThisToParent",tolua_luafunc_cclass_SpriteNode_TranslateThisToParent00);
    tolua_function(tolua_S,"TranslateRootToThis",tolua_luafunc_cclass_SpriteNode_TranslateRootToThis00);
    tolua_function(tolua_S,"TranslateThisToRoot",tolua_luafunc_cclass_SpriteNode_TranslateThisToRoot00);
    tolua_function(tolua_S,"SetChipGrid",tolua_luafunc_cclass_SpriteNode_SetChipGrid00);
    tolua_function(tolua_S,"SetChipIndex",tolua_luafunc_cclass_SpriteNode_SetChipIndex00);
    tolua_function(tolua_S,"SetChipSpan",tolua_luafunc_cclass_SpriteNode_SetChipSpan00);
    tolua_function(tolua_S,"GetTexture",tolua_luafunc_cclass_SpriteNode_GetTexture00);
    tolua_function(tolua_S,"SetImageName",tolua_luafunc_cclass_SpriteNode_SetImageName00);
    tolua_function(tolua_S,"FetchImage",tolua_luafunc_cclass_SpriteNode_FetchImage00);
    tolua_function(tolua_S,"DrawGL",tolua_luafunc_cclass_SpriteNode_DrawGL00);
    tolua_function(tolua_S,"GetChildCount",tolua_luafunc_cclass_SpriteNode_GetChildCount00);
    tolua_function(tolua_S,"GetChildAt",tolua_luafunc_cclass_SpriteNode_GetChildAt00);
    tolua_function(tolua_S,"AddChild",tolua_luafunc_cclass_SpriteNode_AddChild00);
    tolua_function(tolua_S,"RemoveChild",tolua_luafunc_cclass_SpriteNode_RemoveChild00);
    tolua_function(tolua_S,"RemoveFromParent",tolua_luafunc_cclass_SpriteNode_RemoveFromParent00);
    tolua_function(tolua_S,"SetFont",tolua_luafunc_cclass_SpriteNode_SetFont00);
    tolua_function(tolua_S,"SetText",tolua_luafunc_cclass_SpriteNode_SetText00);
    tolua_function(tolua_S,"SetTextColor",tolua_luafunc_cclass_SpriteNode_SetTextColor00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"DrawSystem","DrawSystem","",tolua_collect_DrawSystem);
   #else
   tolua_cclass(tolua_S,"DrawSystem","DrawSystem","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"DrawSystem");
    tolua_function(tolua_S,"new",tolua_luafunc_cclass_DrawSystem_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_cclass_DrawSystem_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_cclass_DrawSystem_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_cclass_DrawSystem_delete00);
    tolua_function(tolua_S,"AddNode",tolua_luafunc_cclass_DrawSystem_AddNode00);
    tolua_function(tolua_S,"RemoveNode",tolua_luafunc_cclass_DrawSystem_RemoveNode00);
    tolua_function(tolua_S,"DrawGL",tolua_luafunc_cclass_DrawSystem_DrawGL00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CollisionDetector","CollisionDetector","",tolua_collect_CollisionDetector);
   #else
   tolua_cclass(tolua_S,"CollisionDetector","CollisionDetector","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CollisionDetector");
    tolua_function(tolua_S,"new",tolua_luafunc_cclass_CollisionDetector_new00);
    tolua_function(tolua_S,"new_local",tolua_luafunc_cclass_CollisionDetector_new00_local);
    tolua_function(tolua_S,".call",tolua_luafunc_cclass_CollisionDetector_new00_local);
    tolua_function(tolua_S,"delete",tolua_luafunc_cclass_CollisionDetector_delete00);
    tolua_function(tolua_S,"init",tolua_luafunc_cclass_CollisionDetector_init00);
    tolua_function(tolua_S,"add_object",tolua_luafunc_cclass_CollisionDetector_add_object00);
    tolua_function(tolua_S,"search_collided_objects",tolua_luafunc_cclass_CollisionDetector_search_collided_objects00);
    tolua_function(tolua_S,"search_near_objects",tolua_luafunc_cclass_CollisionDetector_search_near_objects00);
    tolua_function(tolua_S,"clear",tolua_luafunc_cclass_CollisionDetector_clear00);
    tolua_function(tolua_S,"get_result",tolua_luafunc_cclass_CollisionDetector_get_result00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"cfunc",0);
  tolua_beginmodule(tolua_S,"cfunc");
   tolua_function(tolua_S,"GetDrawSystem",tolua_luafunc_cfunc_GetDrawSystem00);
   tolua_function(tolua_S,"GetImageLoader",tolua_luafunc_cfunc_GetImageLoader00);
   tolua_function(tolua_S,"GetFont",tolua_luafunc_cfunc_GetFont00);
   tolua_function(tolua_S,"GetMousePos",tolua_luafunc_cfunc_GetMousePos00);
   tolua_function(tolua_S,"ReloadLuaFiles",tolua_luafunc_cfunc_ReloadLuaFiles00);
   tolua_function(tolua_S,"DoLuaFile",tolua_luafunc_cfunc_DoLuaFile00);
   tolua_function(tolua_S,"WaitInputOnError",tolua_luafunc_cfunc_WaitInputOnError00);
   tolua_function(tolua_S,"GetLuaError",tolua_luafunc_cfunc_GetLuaError00);
   tolua_function(tolua_S,"RequestQuit",tolua_luafunc_cfunc_RequestQuit00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"SDL",0);
  tolua_beginmodule(tolua_S,"SDL");
   tolua_function(tolua_S,"SDL_Delay",tolua_luafunc_SDL_SDL_Delay00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_luafunc (lua_State* tolua_S) {
 return tolua_luafunc_open(tolua_S);
};
#endif

