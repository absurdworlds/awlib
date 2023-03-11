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
 * Safer alternative to luaL_setfuncs
 * \param lua The Lua state.
 * \param funcs List of functions.
 */
void set_funcs(lua_State* L, array_view<luaL_Reg> funcs);

/*!
 * Creates metatable with specified methods. Resulting table will
 * be on the Lua stack.
 * \param lua The Lua state.
 * \param funcs List of functions.
 */
AW_LUA_EXP
void create_metatable(lua_State* lua, array_view<luaL_Reg> funcs);


/*!
 * Creates a named metatable with specified methods. Resulting table will
 * be on the stack and placed in the Lua registry table under the specified name.
 * \param lua The Lua state.
 * \param name Name of new metatable
 * \param funcs List of functions.
 * \return Whether the table was created.
 */
AW_LUA_EXP
bool create_metatable(lua_State* lua, const char* name, array_view<luaL_Reg> funcs);



/*!
 * Searches for a metatable with specified name in Lua registry. If it is found,
 * it will be pushed on the Lua stack. Otherwise, it returns false and doesn't push it on stack.
 * \param lua The Lua state.
 * \param name Name of the metatable
 * \param Whether the table exists.
 */
AW_LUA_EXP
bool get_metatable(lua_State* lua, const char* name);

} // namespace aw::lua

#endif // aw_lua_metatable_utils_h
