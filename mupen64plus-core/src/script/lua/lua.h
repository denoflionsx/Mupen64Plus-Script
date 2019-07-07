#ifndef __M64P_LUA_H__
#define __M64P_LUA_H__

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <string.h>

#define M64P_CORE_PROTOTYPES 1
#include "api/script/m64p_lua.h"
#include "api/m64p_frontend.h"
#include "memory/memory.h"
#include "main/rom.h"
#ifdef DBG
#include "api/m64p_debugger.h"
#include "debugger/dbg_types.h"
#include "debugger/debugger.h"
#include "debugger/dbg_breakpoints.h"
#endif

void m64p_lua_load_libs(lua_State *L);

#define LUA_PUSH(L, type, val) lua_push ##type((L), (val))

#define LUA_SET_FIELD(L, idx, name, type, val) do {                  \
	lua_push ##type((L), (val));                                     \
	lua_setfield((L), (idx) < 0 ? ((idx)-1) : (idx), (name));        \
} while(0)

#define LUA_GET_FIELD(L, idx, name, type, dest) do {                 \
	lua_getfield((L), (idx), (name));                                \
	if(lua_is ##type((L), -1)) (dest) = lua_to ##type((L), -1);      \
	else return luaL_error((L),                                      \
		"Invalid value for field '%s' (expected %s, got %s)", #name, \
		#type, luaL_typename(L, -1));                                \
	lua_pop((L), 1);                                                 \
} while(0)

#define LUA_OPT_FIELD(L, idx, name, type, dest, def) do {            \
	lua_getfield((L), (idx), (name));                                \
	if(lua_isnil((L), -1)) (dest) = (def);                           \
	else if(lua_is ##type((L), -1)) (dest) = lua_to ##type((L), -1); \
	else return luaL_error((L),                                      \
		"Invalid value for field '%s' (expected %s, got %s)", name,  \
		#type, luaL_typename(L, -1));                                \
	lua_pop((L), 1);                                                 \
} while(0)

int m64p_lua_map_enum(lua_State *L, int start, int end, const char **names,
const char *enumName);

//other submodules, m64p_lua_*lib.c
void m64p_lua_load_memlib(lua_State *L);
void m64p_lua_load_romlib(lua_State *L);
void m64p_lua_load_osdlib(lua_State *L);
#ifdef DBG
void m64p_lua_load_debuglib(lua_State *L);
#endif

#endif //__M64P_LUA_H__
