#include <lua.hpp>

namespace aw::lua {
} // namespace aw::lua

int main()
{
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);
}
