//Mupen64Plus built-in Python modules.
#include "python.h"
#include "main/main.h"
#include "main/savestates.h"
//
//enum {
//	EMU_FIELD_STATE,
//	EMU_FIELD_STATE_SLOT,
//	EMU_FIELD_VIDEO_MODE,
//	EMU_FIELD_SPEED_FACTOR,
//	EMU_FIELD_SPEED_LIMITER,
//	EMU_FIELD_VIDEO_SIZE,
//	EMU_FIELD_AUDIO_VOLUME,
//	EMU_FIELD_AUDIO_MUTE,
//	NUM_EMU_FIELDS
//};
//static const char *emuFieldName[] = {"state", "stateSlot", "videoMode",
//	"speed", "speedLimiter", "videoSize", "audioVolume", "audioMute", NULL};
//
////M64EMU_*
//static const char *emuStateName[] = {"stopped", "running", "paused", NULL};
//
////M64VIDEO_*
//static const char *videoModeName[] = {"none", "windowed", "fullscreen", NULL};
//
//static int emu_meta_index(lua_State *L) {
//	lua_getfield(L, LUA_REGISTRYINDEX, "emu_fields"); //-1: fields
//	lua_pushvalue(L, 2); //-1: key, -2: fields
//	lua_gettable(L, -2); //-1: val, -2: fields
//	int field = luaL_optinteger(L, -1, -1);
//	lua_pop(L, 2);
//
//	switch(field) {
//		case EMU_FIELD_STATE: {
//			int state = 0;
//			main_core_state_query(M64CORE_EMU_STATE, &state);
//			lua_getfield(L, LUA_REGISTRYINDEX, "emu_states"); //-1: states
//			lua_rawgeti(L, -1, state); //-1: val, -2: states
//			lua_remove(L, -2); //-1: val (XXX necessary?)
//			return 1;
//		}
//
//		case EMU_FIELD_STATE_SLOT:
//			lua_pushinteger(L, savestates_get_slot());
//			return 1;
//
//		case EMU_FIELD_VIDEO_MODE: {
//			int mode = 0;
//			int err = main_core_state_query(M64CORE_VIDEO_MODE, &mode);
//			if(err) return luaL_error(L, "%s", m64p_lua_get_err_string(err));
//
//			lua_getfield(L, LUA_REGISTRYINDEX, "video_modes"); //-1: modes
//			lua_rawgeti(L, -1, mode); //-1: val, -2: modes
//			lua_remove(L, -2); //-1: val
//			return 1;
//		}
//
//		case EMU_FIELD_SPEED_FACTOR: {
//			int speed = 0;
//			main_core_state_query(M64CORE_SPEED_FACTOR, &speed);
//			lua_pushnumber(L, (double)speed / 100.0);
//			return 1;
//		}
//
//		case EMU_FIELD_SPEED_LIMITER: {
//			//higher number = slower (larger delay in VI)
//			int limit = 0;
//			main_core_state_query(M64CORE_SPEED_LIMITER, &limit);
//			lua_pushinteger(L, limit);
//			return 1;
//		}
//
//		case EMU_FIELD_VIDEO_SIZE: {
//			int width, height;
//			main_get_screen_size(&width, &height);
//			lua_createtable(L, 0, 2);
//			LUA_SET_FIELD(L, -1, "width",  integer, width);
//			LUA_SET_FIELD(L, -1, "height", integer, height);
//			return 1;
//		}
//
//		case EMU_FIELD_AUDIO_VOLUME: {
//			int vol = 0;
//			int err = main_core_state_query(M64CORE_AUDIO_VOLUME, &vol);
//			if(err) return luaL_error(L, "%s", m64p_lua_get_err_string(err));
//			lua_pushinteger(L, (double)vol / 100.0);
//			return 1;
//		}
//
//		case EMU_FIELD_AUDIO_MUTE: {
//			lua_pushboolean(L, main_volume_get_muted());
//			return 1;
//		}
//
//		//XXX M64CORE_INPUT_GAMESHARK (what does that even do)
//
//		default:
//			lua_pushnil(L);
//			return 1;
//	}
//}
//
//
//static int emu_meta_newindex(lua_State *L) {
//	lua_getfield(L, LUA_REGISTRYINDEX, "emu_fields"); //-1: fields
//	lua_pushvalue(L, 2); //-1: key, -2: fields
//	lua_gettable(L, -2); //-1: val, -2: fields
//	int field = luaL_optinteger(L, -1, -1);
//	lua_pop(L, 2);
//
//	int err = 0;
//	switch(field) {
//		case EMU_FIELD_STATE: {
//			int state = 0, isnum = 0;
//			lua_getfield(L, LUA_REGISTRYINDEX, "emu_states"); //-1: states
//			lua_pushvalue(L, 3); //-1: key, -2: states
//			lua_rawget(L, -2); //-1: state, -2: states
//			state = lua_tointegerx(L, -1, &isnum);
//			lua_pop(L, 2);
//
//			if(isnum) err = main_core_state_set(M64CORE_EMU_STATE, state);
//			else return luaL_error(L, "Invalid state");
//			break;
//		}
//
//		case EMU_FIELD_STATE_SLOT: {
//			int slot = luaL_checkinteger(L, 3);
//			err = main_core_state_set(M64CORE_SAVESTATE_SLOT, slot);
//			break;
//		}
//
//		case EMU_FIELD_VIDEO_MODE: {
//			int mode = 0, isnum = 0;
//			lua_getfield(L, LUA_REGISTRYINDEX, "video_modes"); //-1: modes
//			lua_pushvalue(L, 3); //-1: key, -2: modes
//			lua_rawget(L, -2); //-1: mode, -2: modes
//			mode = lua_tointegerx(L, -1, &isnum);
//			lua_pop(L, 2);
//
//			if(isnum) err = main_core_state_set(M64CORE_VIDEO_MODE, mode);
//			break;
//		}
//
//		case EMU_FIELD_SPEED_FACTOR:
//			err = main_core_state_set(M64CORE_SPEED_FACTOR,
//				luaL_checknumber(L, 3) * 100);
//			break;
//
//		case EMU_FIELD_SPEED_LIMITER:
//			err = main_core_state_set(M64CORE_SPEED_LIMITER,
//				luaL_checkinteger(L, 3));
//			break;
//
//		case EMU_FIELD_VIDEO_SIZE: {
//			int width=0, height=0;
//			if(!lua_istable(L, 3)) return luaL_argerror(L, 3, "expected size");
//
//			lua_getfield(L, 3, "width");
//			width = lua_tointeger(L, -1); //assigns 0 if not integer
//			lua_pop(L, 1);
//
//			lua_getfield(L, 3, "height");
//			height = lua_tointeger(L, -1);
//			lua_pop(L, 1);
//
//			if(width < 1 || height < 1 || width > 65535 || height > 65535)
//				return luaL_error(L, "%s", "Invalid size");
//
//			err = main_core_state_set(M64CORE_VIDEO_SIZE,
//				(width << 16) | height);
//			break;
//		}
//
//		case EMU_FIELD_AUDIO_VOLUME:
//			err = main_core_state_set(M64CORE_AUDIO_VOLUME,
//				luaL_checknumber(L, 3) * 100);
//			break;
//
//		case EMU_FIELD_AUDIO_MUTE:
//			err = main_core_state_set(M64CORE_AUDIO_MUTE,
//				lua_toboolean(L, 3));
//			break;
//
//		//XXX M64CORE_INPUT_GAMESHARK (what does that even do)
//
//		default:
//			if(lua_tostring(L, 2))
//				return luaL_error(L, "Cannot assign to field '%s' in emu",
//					lua_tostring(L, 2));
//			else return luaL_error(L, "Cannot assign to field (%s) in emu",
//				luaL_typename(L, 2));
//	}
//
//	if(err) return luaL_error(L, "%s", m64p_lua_get_err_string(err));
//	return 0;
//}
//
//
//static int emu_run(lua_State *L) {
//	return m64p_lua_return_errcode(L,
//		CoreDoCommand(M64CMD_EXECUTE, 0, NULL));
//}
//
//
//static int emu_stop(lua_State *L) {
//	return m64p_lua_return_errcode(L,
//		CoreDoCommand(M64CMD_STOP, 0, NULL));
//}
//
//
//static int emu_pause(lua_State *L) {
//	return m64p_lua_return_errcode(L,
//		CoreDoCommand(M64CMD_PAUSE, 0, NULL));
//}
//
//
//static int emu_resume(lua_State *L) {
//	return m64p_lua_return_errcode(L,
//		CoreDoCommand(M64CMD_RESUME, 0, NULL));
//}
//
//
//static int emu_register_callback(lua_State *L) {
//	luaL_checktype(L, 3, LUA_TFUNCTION);
//
//	char tname[256];
//	const char *name = luaL_checkstring(L, 2);
//	snprintf(tname, sizeof(tname), "%s_callbacks", name);
//
//	lua_getfield(L, LUA_REGISTRYINDEX, tname);
//	if(!lua_istable(L, -1)) return luaL_error(L, "Invalid callback ID");
//	//-1: callbacks tbl
//
//	//scan this table until we find an empty slot
//	int i=0, done=0;
//	while(!done) {
//		lua_rawgeti(L, -1, ++i); //-1: slot, -2: tbl
//		if(!lua_isfunction(L, -1)) done = 1;
//		lua_pop(L, 1); //-1: tbl
//	}
//
//	lua_pushvalue(L, 3); //-1: func, -2: tbl
//	lua_rawseti(L, -2, i); //-1: tbl
//	lua_pop(L, 1); //remove tbl
//
//	lua_pushboolean(L, 1);
//	return 1;
//}
//
//
//static int emu_unregister_callback(lua_State *L) {
//	luaL_checktype(L, 3, LUA_TFUNCTION);
//
//	char tname[256];
//	const char *name = luaL_checkstring(L, 2);
//	snprintf(tname, sizeof(tname), "%s_callbacks", name);
//
//	lua_getfield(L, LUA_REGISTRYINDEX, tname);
//	if(!lua_istable(L, -1)) return luaL_error(L, "Invalid callback ID");
//	//-1: callbacks tbl
//
//	//scan this table until we find the given function.
//	int i=0, done=0, found=0;
//	while(!done) {
//		lua_rawgeti(L, -1, ++i); //-1: slot, -2: tbl
//		if(lua_isnil(L, -1)) done = 1;
//		else if(lua_compare(L, -1, 2, LUA_OPEQ)) { //value == arg2
//			//replace with a non-function, non-nil value.
//			lua_pushboolean(L, 0); //-1: false, -2: slot, -3: tbl
//			lua_rawseti(L, -3, i); //-1: slot, -2: tbl
//			found = 1; done = 1;
//		}
//		lua_pop(L, 1); //-1: tbl
//	}
//
//	lua_pop(L, 1); //remove tbl
//	lua_pushboolean(L, found);
//	return 1;
//}
//
//
//void m64p_lua_load_libs(lua_State *L) {
//	int i;
//
//	//emulator state table
//	//these are the M64EMU_* in m64p_types.h which for some inexplicable reason
//	//begin at 1 and don't have a "count" or "last" value
//	lua_createtable(L, 0, 6);
//	for(i=1; i<=M64EMU_PAUSED; i++) {
//		//printf("set emu state '%s' = %d\n", emuStateName[i-1], i);
//		LUA_SET_FIELD(L, -1, emuStateName[i-1], integer, i);
//		lua_pushstring(L, emuStateName[i-1]);
//		lua_rawseti(L, -2, i);
//	}
//	lua_setfield(L, LUA_REGISTRYINDEX, "emu_states");
//
//
//	//video modes
//	lua_createtable(L, 0, 6);
//	for(i=1; i<=M64VIDEO_FULLSCREEN; i++) {
//		LUA_SET_FIELD(L, -1, videoModeName[i-1], integer, i);
//		lua_pushstring(L, videoModeName[i-1]);
//		lua_rawseti(L, -2, i);
//	}
//	lua_setfield(L, LUA_REGISTRYINDEX, "video_modes");
//
//
//	//table of emu field names
//	lua_createtable(L, 0, NUM_EMU_FIELDS);
//	for(i=0; emuFieldName[i]; i++) {
//		lua_pushinteger(L, i);
//		lua_setfield(L, -2, emuFieldName[i]);
//	}
//	lua_setfield(L, LUA_REGISTRYINDEX, "emu_fields");
//
//
//	//create callback tables
//	lua_newtable(L);
//	lua_setfield(L, LUA_REGISTRYINDEX, "vi_callbacks");
//	lua_newtable(L);
//	lua_setfield(L, LUA_REGISTRYINDEX, "render_callbacks");
//
//
//	//global m64p table
//	static const luaL_Reg funcs_m64p[] = {
//		{"run",                emu_run},
//		{"stop",               emu_stop},
//		{"pause",              emu_pause},
//		{"resume",             emu_resume},
//		{"registerCallback",   emu_register_callback},
//		{"unregisterCallback", emu_unregister_callback},
//		{NULL, NULL}
//	};
//	luaL_newlib(L, funcs_m64p); //-1: m64p
//
//	//load m64p submodules into m64p table
//	m64p_lua_load_memlib(L);   lua_setfield(L, -2, "memory");
//	m64p_lua_load_romlib(L);   lua_setfield(L, -2, "rom");
//	m64p_lua_load_osdlib(L);   lua_setfield(L, -2, "osd");
//#ifdef DBG
//	m64p_lua_load_debuglib(L); lua_setfield(L, -2, "debug");
//#endif
//
//
//	//m64p metatable
//	static const luaL_Reg meta_m64p[] = {
//		{"__index",    emu_meta_index},
//		{"__newindex", emu_meta_newindex},
//		{NULL, NULL}
//	};
//	luaL_newlib(L, meta_m64p); //-1: meta, -2: m64p
//	lua_setmetatable(L, -2); //-1: m64p
//
//
//	//install m64p table as global variable
//	lua_setglobal(L, "m64p");
//}
