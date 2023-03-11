#include "aw/lua/metatable_utils.h"

namespace aw::lua {
void set_funcs(lua_State* L, array_view<luaL_Reg> funcs)
{
	for (const auto& reg : funcs) {
		lua_pushcclosure(L, reg.func, 0);
		lua_setfield(L, -2, reg.name);
	}
}

void create_metatable(lua_State* L, array_view<luaL_Reg> funcs)
{
	lua_newtable(L);
	set_funcs(L, funcs);
}

bool create_metatable(lua_State* L, const char* name, array_view<luaL_Reg> funcs)
{
	const auto ret = luaL_newmetatable(L, name);
	if (!ret)
		return false;
	set_funcs(L, funcs);
	return true;
}

bool get_metatable(lua_State* L, const char* name)
{
	if (luaL_getmetatable(L, name) != LUA_TNIL)
		return true;
	lua_pop(L, 1);
	return false;
}

} // namespace aw::lua
