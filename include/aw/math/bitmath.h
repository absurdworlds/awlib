/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_math_bitwise
#define _aw_math_bitwise
#include <aw/math/math.h>
namespace aw {
namespace math {
/*!
 * Value with Nth bit set and other bits cleared,
 * counting from 0.
 * (0 is lsb, 31 is msb)
 */
constexpr u64 bit(size_t N)
{
	return 1 << N;
}

//! Check if value is a power of 2
inline bool isPowerOf2(u32 value)
{
	return value && !(value & (value - 1));
}

//! Truncate integer to 8 bits
template<typename integer_type>
inline u8 mask8(integer_type val)
{
	return u8(val & 0xFF);
}

//! Truncate integer to 16 bits
template<typename integer_type>
inline u16 mask16(integer_type val)
{
	return u16(val & 0xFFFF);
}

//! Truncate integer to 32 bits
template<typename integer_type>
inline u32 mask32(integer_type val)
{
	return u32(val & 0xFFFFFFFF);
}

/*!
 * Rotate 32-bit integer to the left
 */
inline u32 rotl(u32 x, size_t r)
{
#if defined(_MSC_VER)
	return _rotl(x,r);
#else
	assert(r < 33);
	return (x << r) | (x >> (32 - r));
#endif
}

/*!
 * Rotate 64-bit integer to the left
 */
inline u64 rotl(u64 x, size_t r)
{
#if defined(_MSC_VER)
	return _rotl64(x,r);
#else
	assert(r < 65);
	return (x << r) | (x >> (64 - r));
#endif
}

/*!
 * Rotate 32-bit integer to the right
 */
inline u32 rotr(u32 x, size_t r)
{
#if defined(_MSC_VER)
	return _rotl(x,r);
#else
	assert(r < 33);
	return (x >> r) | (x << (32 - r));
#endif
}

/*!
 * Rotate 64-bit integer to the right
 */
inline u64 rotr(u64 x, size_t r)
{
#if defined(_MSC_VER)
	return _rotr64(x,r);
#else
	assert(r < 65);
	return (x >> r) | (x << (64 - r));
#endif
}
} //namespace math
} //namespace aw
#endif //_aw_math_
