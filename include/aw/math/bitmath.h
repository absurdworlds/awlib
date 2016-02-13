/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
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

/*!
 * Create mask with upper half bits set to 1
 * and lower bits set to 0.
 * Example: halfMask(4) = 0xFF00
 */
constexpr u64 halfMask(size_t bits)
{
	return ((u64(1) << bits) - 1) << bits;
}

/*!
 * Extract bit value from integer
 */
template <typename Int>
constexpr Int getBit(Int val, size_t idx)
{
	assert(idx < std::numeric_limits<Int>::digits);
	return (val >> idx) & 1;
}

/*!
 * Swap to bits in an integer:
 * swapBits(0b01000, 3, 4) -> 0b10000
 */
template <typename Int>
constexpr Int swapBits(Int val, size_t idx1, size_t idx2)
{
	assert(idx1 < std::numeric_limits<Int>::digits);
	assert(idx2 < std::numeric_limits<Int>::digits);
	Int diff = getBit(val, idx1) ^ getBit(val, idx2);
	return val ^ ((diff << idx1) | (diff << idx2));
}

//! Compute log2 of an integer value
template <typename Int>
constexpr size_t log2(Int value)
{
	constexpr u64 powers[] = {
		0, 1, 2, 4, 8, 16, 32
	};
	constexpr u64 lookup[] = {
	       0,
	       halfMask(1), halfMask(2),  halfMask(4),
	       halfMask(8), halfMask(16), halfMask(32)
	};

	Int result = 0;
	for (size_t i = 6; i > 0; --i) {
		if (value & lookup[i]) {
			value >>= powers[i];
			result |= powers[i];
		}
	}

	return result;
}

//! Check if value is a power of 2
template <typename Int>
constexpr bool isPowerOf2(Int value)
{
	return value && !(value & (value - 1));
}

//! Truncate integer to 8 bits
template<typename Int>
inline u8 mask8(Int val)
{
	return u8(val & 0xFF);
}

//! Truncate integer to 16 bits
template<typename Int>
inline u16 mask16(Int val)
{
	return u16(val & 0xFFFF);
}

//! Truncate integer to 32 bits
template<typename Int>
inline u32 mask32(Int val)
{
	return u32(val & 0xFFFFFFFF);
}

/*!
 * Rotate 32-bit integer to the left
 */
inline u32 rotl(u32 x, size_t r)
{
#if AW_COMPILER == AW_COMPILER_MSVC
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
#if AW_COMPILER == AW_COMPILER_MSVC
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
#if AW_COMPILER == AW_COMPILER_MSVC
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
#if AW_COMPILER == AW_COMPILER_MSVC
	return _rotr64(x,r);
#else
	assert(r < 65);
	return (x >> r) | (x << (64 - r));
#endif
}
} //namespace math
} //namespace aw
#endif //_aw_math_
