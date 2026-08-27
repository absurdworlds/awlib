/*
 * Copyright (C) 2014-2026 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_bit_mask_h
#define aw_bit_mask_h
#include <aw/types/types.h>

#include <limits>
namespace aw::bit {
//! Number of radix digits in type \a T
template<typename T>
constexpr size_t num_digits = std::numeric_limits<T>::digits;

/*!
 * Value with Nth bit set and other bits cleared,
 * counting from 0.
 * (0 is lsb, 31 is msb)
 */
template<typename Int = uintmax_t>
constexpr Int bit(size_t N)
{
	return Int(1) << N;
}

/*!
 * Create mask with lower \a bits bits set to 1
 * and upper bits set to 0.
 * Example: lower_mask<u16>(8) = 0x00FF
 */
template<typename Int>
constexpr Int lower_mask(size_t bits)
{
	return (Int(1) << bits) - 1;
}

/*!
 * Create mask with \a bits bits set to 1,
 * starting right above the lower \a bits bits.
 * Example: upper_mask<u16>(8) = 0xFF00
 */
template<typename Int>
constexpr Int upper_mask(size_t bits)
{
	return (lower_mask<Int>(bits)) << bits;
}

namespace _impl {
template<typename Int>
struct mask {
	static constexpr size_t digits = num_digits<Int>;
	static_assert(digits % 2 == 0, "Type must have an even number of digits");

	static constexpr Int lower_bits = lower_mask<Int>(digits / 2);
	static constexpr Int upper_bits = upper_mask<Int>(digits / 2);
};
} // namespace _impl

//! Mask covering the lower half of \a Int
template<typename Int> constexpr Int lower_bits = _impl::mask<Int>::lower_bits;
//! Mask covering the upper half of \a Int
template<typename Int> constexpr Int upper_bits = _impl::mask<Int>::upper_bits;
} // namespace aw::bit
#endif//aw_bit_mask_h
