/*
 * Copyright (C) 2020 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_builtins_h
#define aw_builtins_h
#include <aw/config.h>
namespace aw {

[[noreturn]] inline void _unreachable()
{
#if AW_EXT(__builtin_unreachable)
	__builtin_unreachable();
#elif AW_EXT(__assume)
	__assume(0);
#endif
}

} // namespace aw

#endif//aw_builtins_h
