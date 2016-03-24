/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pointer_math_h
#define aw_pointer_math_h
#include <aw/types/types.h>

namespace aw {
/*! Align the address to N (power of 2) byte boundry, rounded up */
inline char* alignUp(char* addr, u8 align)
{
	return (addr + static_cast<char*>(align - 1)) & ~static_cast<char*>(align - 1);
}

/*! Align the address to N (power of 2) byte boundry, rounded down */
inline char* alignDown(char* addr, u8 align)
{
	return addr & ~static_cast<char*>(align - 1);
}
} // namespace aw
#endif//aw_pointer_math_h
