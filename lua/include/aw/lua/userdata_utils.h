/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_userdata_utils_h
#define aw_lua_userdata_utils_h

#include <aw/lua/export.h>

#include <lua.hpp>

namespace aw::lua {

template<typename T>
void create_userdata_pointer(lua_State* L, T* instance)
{
	void* ptr = lua_newuserdata(L, sizeof(void*));
	*reinterpret_cast<T**>(ptr) = instance;
}

} // namespace aw::lua

#endif // aw_lua_userdata_utils_h
