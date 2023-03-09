#include "aw/lua/metatable_utils.h"

namespace aw::lua {
void create_metatable(lua_State* L, array_view<luaL_Reg> funcs)
{
	lua_newtable(L);
	for (const auto& reg : funcs) {
		lua_pushcclosure(L, reg.func, 0);
		lua_setfield(L, -2, reg.name);
	}
}

} // namespace aw::lua
