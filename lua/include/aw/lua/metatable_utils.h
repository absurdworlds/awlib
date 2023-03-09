/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_metatable_utils_h
#define aw_lua_metatable_utils_h

#include <aw/lua/export.h>

#include <aw/types/array_view.h>

#include <lua.hpp>


namespace aw::lua {

/*!
 * Creates metatable with specified methods. Resulting table will
 * be on the Lua stack.
 * \param lua The Lua state.
 * \param funcs List of functions.
 */
AW_LUA_EXP
void create_metatable(lua_State* lua, array_view<luaL_Reg> funcs);


} // namespace aw::lua

#endif // aw_lua_metatable_utils_h
