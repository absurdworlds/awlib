/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_types_
#define _awrts_types_
#include <cstddef>
#include <cstdint>

namespace awrts {
#if defined(_MSC_VER)
	typedef unsigned __int8         u8;
	typedef signed __int8           i8;

	typedef unsigned __int16        u16;
	typedef signed __int16          i16;

	typedef unsigned __int32        u32;
	typedef signed __int32          i32;

	typedef signed __int64          i64;
	typedef unsigned __int64        u64;
#else
	typedef uint8_t                 u8;
	typedef  int8_t                 i8;

	typedef uint16_t                u16;
	typedef  int16_t                i16;

	typedef uint32_t                u32;
	typedef  int32_t                i32;

	typedef uint64_t                u64;
	typedef  int64_t                i64;
#endif

typedef float                           f32;
typedef double                          f64;

typedef u8 byte;

#if defined (HR_64BIT) 
	typedef u64 handle;
#else
	typedef u32 handle;
#endif
} // namespace awrts
#endif //_awrts_types_
