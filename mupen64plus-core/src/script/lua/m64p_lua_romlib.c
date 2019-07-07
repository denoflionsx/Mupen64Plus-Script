#include "lua.h"

enum {
	ROM_FIELD_HEADER,
	ROM_FIELD_SETTINGS,
	NUM_ROM_FIELDS
};
static const char *romFieldName[] = {"header", "settings", NULL};


static int rom_open(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	return m64p_lua_return_errcode(L,
		CoreDoCommand(M64CMD_ROM_OPEN, 0, (void*)path));
}


static int rom_close(lua_State *L) {
	return m64p_lua_return_errcode(L,
		CoreDoCommand(M64CMD_ROM_CLOSE, 0, NULL));
}


static int rom_meta_index(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "rom_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(field) {
		case ROM_FIELD_HEADER: {
			m64p_rom_header header;
			if(CoreDoCommand(M64CMD_ROM_GET_HEADER, sizeof(header), &header)) {
				lua_pushnil(L);
				break;
			}

			//ensure name is null terminated.
			char name[sizeof(header.Name)+1];
			strncpy(name, (char*)header.Name, sizeof(name));

			lua_createtable(L, 0, 16); //-1: tbl
			LUA_SET_FIELD(L, -1, "init_PI_BSB_DOM1_LAT_REG", integer,
				header.init_PI_BSB_DOM1_LAT_REG);
			LUA_SET_FIELD(L, -1, "init_PI_BSB_DOM1_PGS_REG", integer,
				header.init_PI_BSB_DOM1_PGS_REG);
			LUA_SET_FIELD(L, -1, "init_PI_BSB_DOM1_PWD_REG", integer,
				header.init_PI_BSB_DOM1_PWD_REG);
			LUA_SET_FIELD(L, -1, "init_PI_BSB_DOM1_PGS_REG2", integer,
				header.init_PI_BSB_DOM1_PGS_REG2);
			LUA_SET_FIELD(L, -1, "ClockRate", integer, header.ClockRate);
			LUA_SET_FIELD(L, -1, "PC",        integer, header.PC);
			LUA_SET_FIELD(L, -1, "Release",   integer, header.Release);
			LUA_SET_FIELD(L, -1, "CRC1",      integer, header.CRC1);
			LUA_SET_FIELD(L, -1, "CRC2",      integer, header.CRC2);
			LUA_SET_FIELD(L, -1, "_x18",      integer, header.Unknown[0]);
			LUA_SET_FIELD(L, -1, "_x1C",      integer, header.Unknown[1]);
			LUA_SET_FIELD(L, -1, "Name", string,  name);
			LUA_SET_FIELD(L, -1, "_x34", integer, header.unknown);
			LUA_SET_FIELD(L, -1, "Manufacturer_ID", integer,
				header.Manufacturer_ID);
			LUA_SET_FIELD(L, -1, "Cartridge_ID", integer, header.Cartridge_ID);
			LUA_SET_FIELD(L, -1, "Country_code", integer, header.Country_code);
			break;
		}

		case ROM_FIELD_SETTINGS: {
			m64p_rom_settings settings;
			if(CoreDoCommand(M64CMD_ROM_GET_SETTINGS,
			  sizeof(settings), &settings)) {
				lua_pushnil(L);
				break;
			}

			lua_createtable(L, 0, 6); //-1: tbl
			LUA_SET_FIELD(L, -1, "goodname", string,  settings.goodname);
			LUA_SET_FIELD(L, -1, "MD5",      string,  settings.MD5);
			LUA_SET_FIELD(L, -1, "savetype", integer, settings.savetype);
			LUA_SET_FIELD(L, -1, "status",   integer, settings.status);
			LUA_SET_FIELD(L, -1, "players",  integer, settings.players);
			LUA_SET_FIELD(L, -1, "rumble",   boolean, settings.rumble);
			break;
		}

		default:
			lua_pushnil(L);
	}

	return 1;
}


void m64p_lua_load_romlib(lua_State *L) {
	//table of ROM field names
	lua_createtable(L, 0, NUM_ROM_FIELDS);
	int i; for(i=0; romFieldName[i]; i++) {
		lua_pushinteger(L, i);
		lua_setfield(L, -2, romFieldName[i]);
	}
	lua_setfield(L, LUA_REGISTRYINDEX, "rom_fields");


	//m64p.rom table
	static const luaL_Reg funcs_rom[] = {
		{"open",   rom_open},
		{"close",  rom_close},
		{NULL, NULL}
	};
	luaL_newlib(L, funcs_rom); //-1: rom


	//m64p.rom metatable
	static const luaL_Reg meta_rom[] = {
		{"__index", rom_meta_index},
		{NULL, NULL}
	};
	luaL_newlib(L, meta_rom); //-1: meta, -2: rom
	lua_setmetatable(L, -2); //-1: rom
}
