/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_pointer_math_
#define _awrts_pointer_math_

#include <awrts/common/types.h>

namespace awrts {

/*! Align the address to N (power of 2) byte boundry, rounded up */
inline void* alignUp(void* addr, u8 align)
{
	return (void *)(((u8*)(addr) + (u8*)(align - 1)) & ~(u8*)(align - 1));
}

/*! Align the address to N (power of 2) byte boundry, rounded down */
inline void* alignDown(void* addr, u8 align)
{
	return (void *)((u8*)(addr) & ~(u8*)(align - 1));
}

} // namespace awrts
#endif//_awrts_pointer_math_
