#include "lua.h"
#include "osd/osd.h"

static const char *OSD_MESSAGE_METATABLE = "osdMessage";

enum {
	//ROM_FIELD_HEADER,
	NUM_OSD_FIELDS
};
static const char *osdFieldName[] = {/* "header", */ NULL};

enum {
	MSG_FIELD_TEXT,
	MSG_FIELD_POSITION,
	MSG_FIELD_COLOR,
	MSG_FIELD_STATIC,
	NUM_MSG_FIELDS
};
static const char *msgFieldName[] = {
	"text", "position", "color", "static", NULL};


//osd_corner
static const char *osdCornerName[] = {
	"topLeft",    "topCenter",    "topRight",
	"midLeft",    "midCenter",    "midRight",
	"bottomLeft", "bottomCenter", "bottomRight", NULL };

//osd_animation_type
static const char *osdAnimTypeName[] = {NULL, "fade", NULL};


static int get_enum(lua_State *L, int idx, const char *field, const char *tbl,
int def) {
	int val = def;

	lua_getfield(L, LUA_REGISTRYINDEX, tbl); //-1: tbl
	lua_getfield(L, idx, field); //-1: name, -2: tbl
	if(!lua_isnil(L, -1)) {
		lua_gettable(L, -2); //-1: val, -2: tbl
		if(lua_isnil(L, -1)) return luaL_error(L,
			"Invalid value for field '%s'", field);
		val = lua_tointeger(L, -1);
	}
	lua_pop(L, 2); //remove val/name, tbl
	return val;
}


static int osd_newMessage(lua_State *L) {
	osd_message_t *msg = NULL;
	if(lua_isstring(L, 1)) {
		msg = osd_new_message(OSD_TOP_LEFT, "%s", luaL_checkstring(L, 1));
	}
	else if(lua_istable(L, 1)) {
		const char *text;
		LUA_OPT_FIELD(L, 1, "text", string, text, "");
		int pos = get_enum(L, 1, "position", "osd_corners", OSD_TOP_LEFT);
		msg = osd_new_message(pos, "%s", text);

		//int anim = get_enum(L, 1, "animType", "osd_anim_types", OSD_NONE);
		//XXX how to set the anim type in msg?

		LUA_OPT_FIELD(L, 1, "xoffset", number, msg->xoffset, 0);
		LUA_OPT_FIELD(L, 1, "yoffset", number, msg->yoffset, 0);

		unsigned int color;
		LUA_OPT_FIELD(L, 1, "color", integer, color, 0xFFFFFF);
		msg->color[B] =  color        & 0xFF;
		msg->color[G] = (color >>  8) & 0xFF;
		msg->color[R] = (color >> 16) & 0xFF;

		lua_getfield(L, 1, "static");
		if(lua_toboolean(L, -1)) osd_message_set_static(msg);
		lua_pop(L, 1);
	}
	else return luaL_argerror(L, 1, "Expected text or table");

	osd_message_set_user_managed(msg);

	//create the Lua object
	osd_message_t **obj = (osd_message_t**)lua_newuserdata(
		L, sizeof(osd_message_t*));
	*obj = msg;
	lua_getfield(L, LUA_REGISTRYINDEX, OSD_MESSAGE_METATABLE);
	lua_setmetatable(L, -2);

	return 1;
}


static int osd_meta_index(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "osd_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(field) {
		//case OSD_FIELD_xxx:
		//	break;

		default:
			lua_pushnil(L);
	}

	return 1;
}


static int message_meta_index(lua_State *L) {
	osd_message_t *msg = *(osd_message_t**)luaL_checkudata(
		L, 1, OSD_MESSAGE_METATABLE);

	lua_getfield(L, LUA_REGISTRYINDEX, "osd_msg_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(field) {
		case MSG_FIELD_TEXT:
			lua_pushstring(L, msg->text);
			break;

		case MSG_FIELD_POSITION:
			lua_getfield(L, LUA_REGISTRYINDEX, "osd_corners"); //-1: corners
			lua_pushinteger(L, msg->corner); //-1: val, -2: corners
			lua_gettable(L, -2); //-1: name, -2: corners
			lua_remove(L, -2); //-1: name
			break;

		case MSG_FIELD_COLOR:
			lua_pushinteger(L,  ((int)msg->color[B] & 0xFF)
				             | (((int)msg->color[G] & 0xFF) << 8)
				             | (((int)msg->color[G] & 0xFF) << 16));
			break;

		case MSG_FIELD_STATIC:
			lua_pushboolean(L, msg->state == OSD_DISPLAY
				&& msg->timeout[OSD_DISPLAY] == OSD_INFINITE_TIMEOUT);
			break;

		default:
			lua_pushnil(L);
	}

	return 1;
}


static int message_meta_newindex(lua_State *L) {
	osd_message_t *msg = *(osd_message_t**)luaL_checkudata(
		L, 1, OSD_MESSAGE_METATABLE);

	lua_getfield(L, LUA_REGISTRYINDEX, "osd_msg_fields"); //-1: fields
	lua_pushvalue(L, 2); //-1: key, -2: fields
	lua_gettable(L, -2); //-1: val, -2: fields
	int field = luaL_optinteger(L, -1, -1);
	lua_pop(L, 2);

	switch(field) {
		case MSG_FIELD_TEXT:
			osd_update_message(msg, "%s", luaL_checkstring(L, 3));
			break;

		case MSG_FIELD_POSITION:
			lua_getfield(L, LUA_REGISTRYINDEX, "osd_corners"); //-1: corners
			lua_pushvalue(L, 3); //-1: name, -2: corners
			lua_gettable(L, -2); //-1: val, -2: corners
			if(lua_isnil(L, -1)) return luaL_error(L, "Invalid position");
			msg->corner = lua_tointeger(L, -1);
			lua_pop(L, 2);
			break;

		case MSG_FIELD_COLOR: {
			unsigned int color = luaL_checkinteger(L, 3);
			msg->color[B] =  color        & 0xFF;
			msg->color[G] = (color >>  8) & 0xFF;
			msg->color[R] = (color >> 16) & 0xFF;
			break;
		}

		case MSG_FIELD_STATIC:
			if(lua_toboolean(L, 3)) osd_message_set_static(msg);
			else msg->timeout[OSD_DISPLAY] = 60;
			break;

		default:
			if(lua_tostring(L, 2))
				return luaL_error(L, "Cannot assign to field '%s' in message",
					lua_tostring(L, 2));
			else return luaL_error(L, "Cannot assign to field (%s) in message",
				luaL_typename(L, 2));
	}

	return 0;
}


static int message_meta_gc(lua_State *L) {
	osd_message_t **obj = luaL_checkudata(L, 1, OSD_MESSAGE_METATABLE);
	osd_delete_message(*obj);
	free(*obj);
	return 0;
}


void m64p_lua_load_osdlib(lua_State *L) {
	m64p_lua_map_enum(L, 0, NUM_OSD_FIELDS,  osdFieldName,  "osd_fields");
	m64p_lua_map_enum(L, 0, NUM_MSG_FIELDS,  msgFieldName,  "osd_msg_fields");
	m64p_lua_map_enum(L, 0, OSD_NUM_CORNERS, osdCornerName, "osd_corners");
	m64p_lua_map_enum(L, OSD_FADE, OSD_NUM_ANIM_TYPES,
		osdAnimTypeName, "osd_anim_types");

	//message metatable
	static const luaL_Reg meta_message[] = {
		{"__index",    message_meta_index},
		{"__newindex", message_meta_newindex},
		{"__gc",       message_meta_gc},
		{NULL, NULL}
	};
	luaL_newmetatable(L, OSD_MESSAGE_METATABLE); //-1: meta
	luaL_setfuncs(L, meta_message, 0);
	lua_pop(L, 1);


	//m64p.osd table
	static const luaL_Reg funcs_osd[] = {
		{"newMessage", osd_newMessage},
		{NULL, NULL}
	};
	luaL_newlib(L, funcs_osd); //-1: osd


	//m64p.osd metatable
	static const luaL_Reg meta_osd[] = {
		{"__index", osd_meta_index},
		{NULL, NULL}
	};
	luaL_newlib(L, meta_osd); //-1: meta, -2: osd
	lua_setmetatable(L, -2); //-1: osd
}
