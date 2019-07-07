#include "lua.h"

//Do not force the user to enable the Debugging freature
//for acessing memory I/O functions 

#ifdef DBG
#include "debugger/dbg_memory.h"
#else
#include "api/m64p_rdmem.h"
#endif

#include "main/main.h"

enum {
	MEM_TYPE_S8,
	MEM_TYPE_U8,
	MEM_TYPE_S16,
	MEM_TYPE_U16,
	MEM_TYPE_S32,
	MEM_TYPE_U32,
	MEM_TYPE_FLOAT,
	MEM_TYPE_DOUBLE,
	MEM_TYPE_STRING, //used for write
	NUM_MEM_TYPES
};
static const char *memTypeName[] = {
	"s8", "u8", "s16", "u16", "s32", "u32", "float", "double", "string", NULL};

static int mem_meta_index(lua_State *L) {
	if(lua_isinteger(L, 2)) {
		uint32 addr = luaL_checkinteger(L, 2);
		lua_pushinteger(L, read_rdmem_8(addr));
	}
	else {
		lua_getfield(L, LUA_REGISTRYINDEX, "memory_methods"); //-1: methods
		lua_pushvalue(L, 2); //-1: key, -2: methods
		lua_gettable(L, -2); //-1: val, -2: methods
		lua_remove(L, -2); //-1: val
	}
	return 1;
}

static int mem_meta_newindex(lua_State *L) {
	if(lua_isinteger(L, 2)) {
		uint32 addr = luaL_checkinteger(L, 2);
		uint8  val  = luaL_checkinteger(L, 3);
		write_rdmem_8(addr, val);
		return 0;
	}
	else if(lua_tostring(L, 2))
		return luaL_error(L, "Cannot assign to field '%s' in memory",
		lua_tostring(L, 2));
	else return luaL_error(L, "Cannot assign to field (%s) in memory",
		luaL_typename(L, 2));
	return 0;
}


static int mem_method_read(lua_State *L) {
	u32 addr = luaL_checkinteger(L, 2);
	if(lua_isinteger(L, 3)) { //read specified number of bytes as string
		int len = lua_tointeger(L, 3);
		if(len < 1) {
			lua_pushnil(L);
			lua_pushstring(L, "Invalid length");
			return 2;
		}

		//this could be used if the host system byte order allowed for it.
		//XXX will this work with TLB?
		/* if(addr >= 0x80000000 && (addr+len) <= 0x80800000) {
			lua_pushlstring(L, (const char*)(rdramb + (addr & 0xFFFFFF)), len);
		}

		//XXX verify address range
		else if(addr >= 0xB0000000 && (addr+len) <= 0xB4000000) {
			lua_pushlstring(L, (const char*)(rom + (addr & 0xFFFFFF)), len);
		}

		else */ { //fall back to slow method.
			luaL_Buffer buf;
			luaL_buffinitsize(L, &buf, len);
			int i; for(i=0; i<len; i++) {
				luaL_addchar(&buf, read_rdmem_8(addr + i));
			}
			luaL_pushresultsize(&buf, len);
		}
	}
	else { //must be a variable type name
		lua_getfield(L, LUA_REGISTRYINDEX, "mem_types"); //-1: types
		lua_pushvalue(L, 3); //-1: key, -2: types
		lua_gettable(L, -2); //-1: val, -2: types
		int tp = luaL_optinteger(L, -1, -1);
		lua_pop(L, 2);

		switch(tp) {
			case MEM_TYPE_S8:
				lua_pushinteger(L, (s8)read_rdmem_8(addr));
				break;

			case MEM_TYPE_U8:
				lua_pushinteger(L, (u8)read_rdmem_8(addr));
				break;

			case MEM_TYPE_S16:
				lua_pushinteger(L, (s16)read_rdmem_16(addr));
				break;

			case MEM_TYPE_U16:
				lua_pushinteger(L, (u16)read_rdmem_16(addr));
				break;

			case MEM_TYPE_S32:
				lua_pushinteger(L, (s32)read_rdmem_32(addr));
				break;

			case MEM_TYPE_U32:
				lua_pushinteger(L, (u32)read_rdmem_32(addr));
				break;

			case MEM_TYPE_FLOAT: {
				u32 num = read_rdmem_32_unaligned(addr);
				lua_pushnumber(L, *(float*)&num);
				break;
			}

			case MEM_TYPE_DOUBLE: {
				u64 num = read_rdmem_64_unaligned(addr);
				lua_pushnumber(L, *(double*)&num);
				break;
			}

			default:
				lua_pushnil(L);
				lua_pushstring(L, "Invalid type");
				return 2;
		}
	}
	return 1;
}


static int mem_method_write(lua_State *L) {
	u32 addr = luaL_checkinteger(L, 2);

	lua_getfield(L, LUA_REGISTRYINDEX, "mem_types"); //-1: types
	lua_pushvalue(L, 3); //-1: key, -2: types
	lua_gettable(L, -2); //-1: val, -2: types
	int tp = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(tp) {
		case MEM_TYPE_S8:
			write_rdmem_8(addr, (s8)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_U8:
			write_rdmem_8(addr, (u8)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_S16:
			write_rdmem_16(addr, (s16)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_U16:
			write_rdmem_16(addr, (u16)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_S32:
			write_rdmem_32_unaligned(addr, (s32)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_U32:
			write_rdmem_32_unaligned(addr, (u32)luaL_checkinteger(L, 4));
			break;

		case MEM_TYPE_FLOAT: {
			float num = (float)luaL_checknumber(L, 4);
			write_rdmem_32_unaligned(addr, *(u32*)&num);
			break;
		}

		case MEM_TYPE_DOUBLE: {
			double num = (double)luaL_checknumber(L, 4);
			write_rdmem_64_unaligned(addr, *(u64*)&num);
			break;
		}

		case MEM_TYPE_STRING: {
			size_t len;
			const char *str = luaL_checklstring(L, 4, &len);
			int i; for (i = 0; i<len; i++) write_rdmem_8(addr + i, str[i]);
			break;
		}

		default:
			lua_pushnil(L);
			lua_pushstring(L, "Invalid type");
			return 2;
	}

	return 0;
}


void m64p_lua_load_memlib(lua_State *L) {
	//table of memory access variable types.
	lua_createtable(L, 0, NUM_MEM_TYPES);
	int i; for(i=0; memTypeName[i]; i++) {
		lua_pushinteger(L, i);
		lua_setfield(L, -2, memTypeName[i]);
	}
	lua_setfield(L, LUA_REGISTRYINDEX, "mem_types");


	//m64p.memory methods
	static const luaL_Reg methods_mem[] = {
		{"read",  mem_method_read},
		{"write", mem_method_write},
		{NULL, NULL}
	};
	luaL_newlib(L, methods_mem); //-1: methods, -2: m64p
	lua_setfield(L, LUA_REGISTRYINDEX, "memory_methods"); //-1: m64p


	//m64p.memory table
	static const luaL_Reg funcs_mem[] = {
		//{"read", mem_read},
		{NULL, NULL}
	};
	luaL_newlib(L, funcs_mem); //-1: mem


	//m64p.memory metatable
	static const luaL_Reg meta_mem[] = {
		{"__index",    mem_meta_index},
		{"__newindex", mem_meta_newindex},
		{NULL, NULL}
	};
	luaL_newlib(L, meta_mem); //-1: meta, -2: mem
	lua_setmetatable(L, -2); //-1: mem
}

