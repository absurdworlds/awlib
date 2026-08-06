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

#include <aw/utility/type_name.h>

#include <lua.hpp>

#include <string>

namespace aw::lua {

/*!
 * Name under which T's metatable is registered.
 *
 * Lua needs a null-terminated string which outlives the call, so the name is
 * materialized once per type.
 */
template<typename T>
const char* metatable_name()
{
	static const std::string name{ type_name<T>::name() };
	return name.c_str();
}

template<typename T>
void create_userdata_pointer(lua_State* L, T* instance)
{
	void* ptr = lua_newuserdata(L, sizeof(void*));
	*reinterpret_cast<T**>(ptr) = instance;
}

/*!
 * Check that the value at \a index is a T, and return it.
 *
 * Modeled after the luaL_check* family of functions, which
 * likewise return the value and raise a Lua error when it
 * is of the wrong type.
 */
template<typename T>
T* check_userdata_pointer(lua_State* L, int index)
{
	void* ptr = luaL_checkudata(L, index, metatable_name<T>());
	return *static_cast<T**>(ptr);
}

} // namespace aw::lua

#endif // aw_lua_userdata_utils_h
