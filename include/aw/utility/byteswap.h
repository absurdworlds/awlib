/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_byteswap
#define aw_utility_byteswap
#include <aw/utility/utility.h>
#include <aw/types/types.h>
namespace aw {
/*!
 * Switch endiannes of an integer value
 */
u16 byteswap(u16 val)
{
#if   AW_EXT(__builtin_bswap16)
	return __builtin_bswap16(val);
#elif defined(AW_WINDOWS)
	return _byteswap_ushort(val);
#else
	return ((((val >> 0) & 0xFF) << 8) |
	        (((val >> 8) & 0xFF) << 0));
#endif
}

/*!
 * Switch endiannes of an integer value
 */
u32 byteswap(u32 val)
{
#if   AW_EXT(__builtin_bswap32)
	return __builtin_bswap32(val);
#elif defined(AW_WINDOWS)
	return _byteswap_uint(val);
#else
	return ((((val >> 0) & 0xFF) << 24) |
	        (((val >> 8) & 0xFF) << 16) |
	        (((val >> 16) & 0xFF) << 8) |
	        (((val >> 24) & 0xFF) << 0));
#endif
}

/*!
 * Switch endiannes of an integer value
 */
u64 byteswap(u64 val)
{
#if   AW_EXT(__builtin_bswap64)
	return __builtin_bswap64(val);
#elif defined(AW_WINDOWS)
	return _byteswap_ulong(val);
#else
	return ((((val >> 0)  & 0xFF) << 56) |
	        (((val >> 8)  & 0xFF) << 48) |
	        (((val >> 16) & 0xFF) << 40) |
	        (((val >> 24) & 0xFF) << 32) |
	        (((val >> 32) & 0xFF) << 24) |
	        (((val >> 40) & 0xFF) << 16) |
	        (((val >> 48) & 0xFF) << 8)  |
	        (((val >> 56) & 0xFF) << 0));
#endif
}

/*!
 * Switch endiannes of an integer value
 */
i16 byteswap(i16 val)
{
	return i16(byteswap(u16(val)));
}

/*!
 * Switch endiannes of an integer value
 */
i32 byteswap(i32 val)
{
	return i32(byteswap(u32(val)));
}

/*!
 * Switch endiannes of an integer value
 */
i64 byteswap(i64 val)
{
	return i64(byteswap(u64(val)));
}
// namespace aw
#endif//aw_utility_byteswap
