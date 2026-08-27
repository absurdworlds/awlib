/*
 * Copyright (C) 2014-2026 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_bit_manip_h
#define aw_bit_manip_h
#include <aw/bit/mask.h>
#include <aw/meta/conditional.h>
#include <aw/types/traits/basic_traits.h>

#include <cassert>
namespace aw::bit {
//! Lower half of the bits of \a value
template<typename Int>
constexpr Int lower_half(Int value)
{
	return value & lower_bits<Int>;
}

//! Upper half of the bits of \a value, shifted into the lower half
template<typename Int>
constexpr Int upper_half(Int value)
{
	static_assert(num_digits<Int> % 2 == 0, "Type must have an even number of digits");
	return value >> (num_digits<Int> / 2);
}

//! Lower half of the bits of \a value, shifted into the upper half
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
	assert(idx < num_digits<Int>);
	return (val >> idx) & 1;
}

/*!
 * Extract top bit from integer
 */
template <typename Int>
constexpr bool top_bit(Int val)
{
	return get_bit(val, num_digits<Int> - 1);
}

/*!
 * Set bit in position \a idx to \a bitval.
 */
template <typename Int>
constexpr Int set_bit(Int val, size_t idx, bool bitval)
{
	assert(idx < num_digits<Int>);
	Int flag = (Int(bitval) << idx);
	val ^= (val & flag) ^ flag;
	return val;
}

/*!
 * Swap two bits in an integer:
 * swap_bits(0b01000, 3, 4) -> 0b10000
 */
template <typename Int>
constexpr Int swap_bits(Int val, size_t idx1, size_t idx2)
{
	assert(idx1 < num_digits<Int>);
	assert(idx2 < num_digits<Int>);
	Int diff = get_bit(val, idx1) != get_bit(val, idx2);
	return val ^ ((diff << idx1) | (diff << idx2));
}

/*! Rotate unsigned integer towards the left */
template<typename T> enable_if< is_unsigned<T>, T >
constexpr rotl(T x, size_t r)
{
	constexpr auto digits = num_digits<T>;

	// Shift by all bits is UB
	assert(r < digits);

	constexpr auto mask = digits-1;
	return (x << r) | (x >> (-r & mask));
}

/*! Rotate unsigned integer towards the right */
template<typename T> enable_if< is_unsigned<T>, T >
constexpr rotr(T x, size_t r)
{
	constexpr auto digits = num_digits<T>;

	// Shift by all bits is UB
	assert(r < digits);

	constexpr auto mask = digits-1;
	return (x >> r) | (x << (-r & mask));
}
} // namespace aw::bit
#endif//aw_bit_manip_h
