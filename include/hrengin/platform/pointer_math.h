#ifndef _hrengin_pointer_math_
#define _hrengin_pointer_math_

#include <hrengin/common/types.h>

namespace hrengin {

/* align the address to N (power of 2) byte boundry, rounded up */
inline void* alignUp(void* addr, u8 align)
{
	return (void *)( ( (u8*)(addr) + (u8*)(align - 1) ) & ~ (u8*)(align - 1) );
}

/* align the address to N (power of 2) byte boundry, rounded down */
inline void* alignDown(void* addr, u8 align)
{
	return (void *)( (u8*)(addr) & ~ (u8*)(align - 1) );
}

} // namespace hrengin

#endif//_hrengin_pointer_math_
