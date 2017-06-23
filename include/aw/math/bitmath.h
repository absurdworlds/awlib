/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_bitwise_h
#define aw_math_bitwise_h
#include <aw/math/math.h>
#include <aw/math/numeric.h>
namespace aw {
namespace math {
/*!
 * Value with Nth bit set and other bits cleared,
 * counting from 0.
 * (0 is lsb, 31 is msb)
 */
constexpr uintmax_t bit(size_t N)
{
	return 1 << N;
}

/*!
 * Create mask with lower half bits set to 1
 * and upper bits set to 0.
 * Example: lower_mask(4) = 0x00FF
 */
template<typename Int>
constexpr Int lower_mask(size_t bits)
{
	return (Int(1) << bits) - 1;
}

/*!
 * Create mask with upper half bits set to 1
 * and lower bits set to 0.
 * Example: halfMask(4) = 0x00FF
 */
template<typename Int>
constexpr Int upper_mask(size_t bits)
{
	return (lower_mask<Int>(bits)) << bits;
}

namespace _impl {
template<typename Int>
struct mask {
	static_assert(is_even(num_digits<Int>), "");
	static constexpr Int lower_bits = lower_mask<Int>(num_digits<Int> / 2);
	static constexpr Int upper_bits = upper_mask<Int>(num_digits<Int> / 2);
};
} // namespace _impl

template<typename Int> constexpr Int lower_bits = _impl::mask<Int>::lower_bits;
template<typename Int> constexpr Int upper_bits = _impl::mask<Int>::upper_bits;

template<typename Int>
constexpr Int lower_half(Int value)
{
	return value & lower_bits<Int>;
}

template<typename Int>
constexpr Int upper_half(Int value)
{
	static_assert(is_even(num_digits<Int>), "");
	return value >> (num_digits<Int> / 2);
}

template<typename Int>
constexpr Int lower_to_upper(Int value)
{
	return lower_half(value) << (num_digits<Int> / 2);
}

/*!
 * Extract value of a single bit from integer
 */
template <typename Int>
constexpr bool get_bit(Int val, size_t idx)
{
	assert(idx < std::numeric_limits<Int>::digits);
	return (val >> idx) & 1;
}

/*!
 * Extract top bit from integer
 */
template <typename Int>
constexpr bool top_bit(Int val)
{
	return get_bit(val, std::numeric_limits<Int>::digits - 1);
}

/*!
 * Set bit in position \a idx to \a bitval.
 */
template <typename Int>
constexpr Int set_bit(Int val, size_t idx, bool bitval)
{
	assert(idx < std::numeric_limits<Int>::digits);
	Int flag = (bitval << idx);
	val ^= (val & flag) ^ flag;
	return val;
}

/*!
 * Swap two bits in an integer:
 * swapBits(0b01000, 3, 4) -> 0b10000
 */
template <typename Int>
constexpr Int swap_bits(Int val, size_t idx1, size_t idx2)
{
	assert(idx1 < std::numeric_limits<Int>::digits);
	assert(idx2 < std::numeric_limits<Int>::digits);
	Int diff = getBit(val, idx1) != getBit(val, idx2);
	return val ^ ((diff << idx1) | (diff << idx2));
}

//! Compute log2 of an integer value
template <typename Int>
constexpr size_t log2(Int value)
{
	static_assert(num_digits<Int> <= num_digits<u64>, "Type is too large.");
	constexpr u64 powers[] = { 0, 1, 2, 4, 8, 16, 32 };
	constexpr u64 lookup[] = {
	       0,
	       upper_mask<u64>(1),  upper_mask<u64>(2),
	       upper_mask<u64>(4),  upper_mask<u64>(8),
	       upper_mask<u64>(16), upper_mask<u64>(32)
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

inline size_t leading_zeros(u32 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_clz)
	if (x != 0)
		n = __builtin_clz(x);
	else
		n = 32;
#else
	if (x <= 0x0000ffff) {
		n +=  16;
		x <<= 16;
	}
	if (x <= 0x00ffffff) {
		n +=  8;
		x <<= 8;
	}
	if (x <= 0x0fffffff) {
		n +=  4;
		x <<= 4;
	}
	if (x <= 0x3fffffff) {
		n +=  2;
		x <<= 2;
	}

	n += (x <= 0x7fffffff);
#endif

	return n;
}

inline size_t leading_zeros(u64 x)
{
	size_t n = 0;
#if AW_EXT(__builtin_clzll)
	if (x != 0)
		n = __builtin_clzll(x);
	else
		n = 64;
#else
	if (x <= 0x00000000'ffffffff) {
		n +=  32;
		x <<= 32;

		n += leading_zeros(u32(lower_half(x)));
	} else {
		n += leading_zeros(u32(upper_half(x)));
	}
#endif

	return n;
}


inline size_t trailing_zeros(u32 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_ctz)
	if (x != 0)
		n = __builtin_clz(x);
	else
		n = 32;
#else
	if (x & 0x1)
		return 0;

	if ((x & 0xffff) == 0) {
		x >>= 16;
		n  += 16;
	}
	if ((x & 0xff) == 0) {
		x >>= 8;
		n  += 8;
	}
	if ((x & 0xf) == 0) {
		x >>= 4;
		n  += 4;
	}
	if ((x & 0x3) == 0) {
		x >>= 2;
		n  += 2;
	}
	n += x & 0x1;
#endif

	return n;
}

inline size_t trailing_zeros(u64 x)
{
	size_t n = 0;

#if AW_EXT(__builtin_ctzll)
	if (x != 0)
		n = __builtin_ctzll(x);
	else
		n = 64;
#else
	if (x & 0x1)
		return 0;

	if ((x & 0xffffffff) == 0) {
		x >>= 32;
		n  += 32;

		n += trailing_zeros(u32(upper_half(x)));
	} else {
		n += trailing_zeros(u32(lower_half(x)));
	}
#endif

	return n;
}

template <typename T>
size_t clz(T value)
{
	return leading_zeros(value);
}

template <typename T>
size_t ctz(T value)
{
	return trailing_zeros(value);
}
} //namespace math
} //namespace aw
#endif //aw_math_bitwise_h
