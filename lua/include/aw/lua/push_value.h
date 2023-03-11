/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_push_value_h
#define aw_push_value_h

#include <aw/types/string_view.h>

#include <lua.hpp>

#include <concepts>

namespace aw::lua {

template<std::integral T>
void push_value(lua_State* L, T value)
{
	lua_pushinteger(L, value);
}

template<std::floating_point T>
void push_value(lua_State* L, T value)
{
	lua_pushnumber(L, value);
}

template<typename T>
concept convertible_to_string_view = std::convertible_to<T, string_view>;

inline
void push_value(lua_State* L, string_view value)
{
	lua_pushlstring(L, value.data(), value.size());
}

template<convertible_to_string_view T>
void push_value(lua_State* L, T value)
{
	push_value(L, string_view(value));
}

inline
void push_value(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
}

} // namespace aw::lua

#endif // aw_push_value_h
