#if !defined(API_LUA_H)
#define API_LUA_H

#include "api/m64p_types.h"
#include "api/callbacks.h"
#ifdef DBG
#include "debugger/dbg_types.h"
#endif

extern lua_State *g_luaState;

extern int m64p_lua_init();
extern m64p_error m64p_lua_load_script(const char *path);
extern const char* m64p_lua_get_err_string(m64p_error err);
extern int m64p_lua_return_errcode(lua_State *L, m64p_error err);
extern void m64p_lua_render_callback();
extern void m64p_lua_vi_callback();

#ifdef DBG
extern void m64p_lua_handle_breakpoint(
	uint32_t pc, int bpt, unsigned int event);
#endif

#endif //API_LUA_H
