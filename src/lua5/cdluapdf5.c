/** \file
 * \brief PDF Canvas Lua 5 Binding
 *
 * See Copyright Notice in cd.h
 */

#include <stdlib.h>
#include <stdio.h>

#include "cd.h"
#include "cdpdf.h"

#include <lua.h>
#include <lauxlib.h>

#include "cdlua.h"
#include "cdluapdf.h"
#include "cdlua5_private.h"


static void *cdpdf_checkdata(lua_State *L, int param)
{
  return (void *)luaL_checkstring(L, param);
}

static cdluaContext cdluapdfctx = 
{
  0,
  "PDF",
  cdContextPDF,
  cdpdf_checkdata,
  NULL,
  0
};

int cdluapdf_open (lua_State *L)
{
  cdluaLuaState* cdL = cdlua_getstate(L);
  /* leave "cd" table at the top of the stack */
#if LUA_VERSION_NUM > 501
  luaL_openlib(L, "cd", NULL, 0);
#else
  lua_pushliteral(L, "cd");
  lua_gettable(L, LUA_GLOBALSINDEX);  
#endif
  cdlua_addcontext(L, cdL, &cdluapdfctx);
  return 1;
}

int luaopen_cdluapdf(lua_State* L)
{
  return cdluapdf_open(L);
}

