/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_export_h
#define aw_lua_export_h
#include <aw/config.h>
#ifdef AW_MODULE_LUA
#define AW_LUA_EXP AW_EXPORT
#else
#define AW_LUA_EXP AW_IMPORT
#endif
#endif // aw_lua_export_h
