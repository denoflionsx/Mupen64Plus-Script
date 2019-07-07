#include "lua.h"

enum {
	DBG_FIELD_RUN_STATE = 0,
	DBG_FIELD_PREVIOUS_PC,
	DBG_FIELD_NUM_BREAKPOINTS,
	DBG_FIELD_CPU_DYNACORE,
	DBG_FIELD_NEXT_INTERRUPT,
	NUM_DEBUG_FIELDS
};
static const char *debugFieldName[] = {"runState", "prevPC", "numBreakpoints",
	"dynacore", "nextInterrupt", NULL};


static int debug_step(lua_State *L) {
	return m64p_lua_return_errcode(L, DebugStep());
}

static int debug_set_breakpoint(lua_State *L) {
	m64p_breakpoint bkpt;
	LUA_GET_FIELD(L, 1, "address", integer, bkpt.address);
	LUA_OPT_FIELD(L, 1, "endaddr", integer, bkpt.endaddr, bkpt.address);

	int f_enabled, f_read, f_write, f_exec, f_log;
	LUA_OPT_FIELD(L, 1, "enabled", boolean, f_enabled, 1);
	LUA_OPT_FIELD(L, 1, "read",    boolean, f_read,    0);
	LUA_OPT_FIELD(L, 1, "write",   boolean, f_write,   0);
	LUA_OPT_FIELD(L, 1, "exec",    boolean, f_exec,    0);
	LUA_OPT_FIELD(L, 1, "log",     boolean, f_log,     0);

	bkpt.flags =
		(f_enabled ? M64P_BKP_FLAG_ENABLED : 0) |
		(f_read    ? M64P_BKP_FLAG_READ    : 0) |
		(f_write   ? M64P_BKP_FLAG_WRITE   : 0) |
		(f_exec    ? M64P_BKP_FLAG_EXEC    : 0) |
		(f_log     ? M64P_BKP_FLAG_LOG     : 0);

	int idx = add_breakpoint_struct(&bkpt);
	if(idx >= 0) {
		lua_pushinteger(L, idx);
		return 1;
	}
	lua_pushnil(L);
	lua_pushstring(L, "Cannot add any more breakpoints");
	return 2;
}



static int debug_meta_index(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "debug_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(field) {
		case DBG_FIELD_RUN_STATE: {
			int state = DebugGetState(M64P_DBG_RUN_STATE);
			lua_getfield(L, LUA_REGISTRYINDEX, "emu_states"); //-1: states
			lua_rawgeti(L, -1, state); //-1: val, -2: states
			lua_remove(L, -2); //-1: val (XXX necessary?)
			return 1;
		}

		case DBG_FIELD_PREVIOUS_PC: {
			uint32_t pc = DebugGetState(M64P_DBG_PREVIOUS_PC);
			lua_pushinteger(L, pc);
			return 1;
		}

		case DBG_FIELD_NUM_BREAKPOINTS: {
			lua_pushinteger(L, DebugGetState(M64P_DBG_NUM_BREAKPOINTS));
			return 1;
		}

		case DBG_FIELD_CPU_DYNACORE: {
			lua_pushinteger(L, DebugGetState(M64P_DBG_CPU_DYNACORE));
			return 1;
		}

		case DBG_FIELD_NEXT_INTERRUPT: {
			lua_pushinteger(L, DebugGetState(M64P_DBG_CPU_NEXT_INTERRUPT));
			return 1;
		}

		default:
			lua_pushnil(L);
	}

	return 1;
}


static int debug_meta_newindex(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "debug_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	int err = 0;
	switch(field) {
		case DBG_FIELD_RUN_STATE: {
			int state = 0, isnum = 0;
			lua_getfield(L, LUA_REGISTRYINDEX, "emu_states"); //-1: states
			lua_pushvalue(L, 3); //-1: key, -2: states
			lua_rawget(L, -2); //-1: state, -2: states
			state = lua_tointegerx(L, -1, &isnum);
			lua_pop(L, 2);

			if(isnum) err = DebugSetRunState(state);
			else return luaL_error(L, "Invalid state");
			break;
		}

		default:
			if(lua_tostring(L, 2))
				return luaL_error(L, "Cannot assign to field '%s' in debug",
					lua_tostring(L, 2));
			else return luaL_error(L, "Cannot assign to field (%s) in debug",
				luaL_typename(L, 2));
	}

	if(err) return luaL_error(L, "%s", m64p_lua_get_err_string(err));
	return 0;
}


void m64p_lua_load_debuglib(lua_State *L) {
	static int is_init = 0;
	if(!is_init) {
		init_debugger();
		DebugSetRunState(1); //do not start paused
		//we might provide a "before emulation is about to start" callback
		//for scripts that do want to start paused.
		is_init = 1;
	}

	//table of debug field names
	lua_createtable(L, 0, NUM_DEBUG_FIELDS);
	int i; for(i=0; debugFieldName[i]; i++) {
		lua_pushinteger(L, i);
		lua_setfield(L, -2, debugFieldName[i]);
	}
	lua_setfield(L, LUA_REGISTRYINDEX, "debug_fields");


	//m64p.debug table
	static const luaL_Reg funcs_debug[] = {
		{"step",           debug_step},
		{"set_breakpoint", debug_set_breakpoint},
		{NULL, NULL}
	};
	luaL_newlib(L, funcs_debug); //-1: debug


	//m64p.debug metatable
	static const luaL_Reg meta_debug[] = {
		{"__index",    debug_meta_index},
		{"__newindex", debug_meta_newindex},
		{NULL, NULL}
	};
	luaL_newlib(L, meta_debug); //-1: meta, -2: debug
	lua_setmetatable(L, -2); //-1: debug
}
