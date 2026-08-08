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
#include <aw/bit/count.h>
#include <aw/bit/manip.h>
#include <aw/bit/mask.h>
#include <aw/math/math.h>
#include <aw/math/numeric.h>
namespace aw::math {
/*
 * The bit manipulation functions have moved into aw::bit,
 * everything below is kept only until the users are updated.
 */
[[deprecated("Use aw::bit::bit() instead")]]
constexpr uintmax_t bit(size_t N)
{
	return aw::bit::bit(N);
}

template<typename Int>
[[deprecated("Use aw::bit::lower_mask() instead")]]
constexpr Int lower_mask(size_t bits)
{
	return aw::bit::lower_mask<Int>(bits);
}

template<typename Int>
[[deprecated("Use aw::bit::upper_mask() instead")]]
constexpr Int upper_mask(size_t bits)
{
	return aw::bit::upper_mask<Int>(bits);
}

template<typename Int>
[[deprecated("Use aw::bit::lower_bits instead")]]
constexpr Int lower_bits = aw::bit::lower_bits<Int>;

template<typename Int>
[[deprecated("Use aw::bit::upper_bits instead")]]
constexpr Int upper_bits = aw::bit::upper_bits<Int>;

template<typename Int>
[[deprecated("Use aw::bit::lower_half() instead")]]
constexpr Int lower_half(Int value)
{
	return aw::bit::lower_half(value);
}

template<typename Int>
[[deprecated("Use aw::bit::upper_half() instead")]]
constexpr Int upper_half(Int value)
{
	return aw::bit::upper_half(value);
}

template<typename Int>
[[deprecated("Use aw::bit::lower_to_upper() instead")]]
constexpr Int lower_to_upper(Int value)
{
	return aw::bit::lower_to_upper(value);
}

template <typename Int>
[[deprecated("Use aw::bit::get_bit() instead")]]
constexpr bool get_bit(Int val, size_t idx)
{
	return aw::bit::get_bit(val, idx);
}

template <typename Int>
[[deprecated("Use aw::bit::top_bit() instead")]]
constexpr bool top_bit(Int val)
{
	return aw::bit::top_bit(val);
}

template <typename Int>
[[deprecated("Use aw::bit::set_bit() instead")]]
constexpr Int set_bit(Int val, size_t idx, bool bitval)
{
	return aw::bit::set_bit(val, idx, bitval);
}

template <typename Int>
[[deprecated("Use aw::bit::swap_bits() instead")]]
constexpr Int swap_bits(Int val, size_t idx1, size_t idx2)
{
	return aw::bit::swap_bits(val, idx1, idx2);
}

template<typename T>
[[deprecated("Use aw::bit::rotl() instead")]]
constexpr enable_if< is_unsigned<T>, T > rotl(T x, size_t r)
{
	return aw::bit::rotl(x, r);
}

template<typename T>
[[deprecated("Use aw::bit::rotr() instead")]]
constexpr enable_if< is_unsigned<T>, T > rotr(T x, size_t r)
{
	return aw::bit::rotr(x, r);
}

template <typename T>
[[deprecated("Use aw::bit::leading_zeros() instead")]]
size_t leading_zeros(T value)
{
	return aw::bit::leading_zeros(value);
}

template <typename T>
[[deprecated("Use aw::bit::trailing_zeros() instead")]]
size_t trailing_zeros(T value)
{
	return aw::bit::trailing_zeros(value);
}

template <typename T>
[[deprecated("Use aw::bit::clz() instead")]]
size_t clz(T value)
{
	return aw::bit::leading_zeros(value);
}

template <typename T>
[[deprecated("Use aw::bit::ctz() instead")]]
size_t ctz(T value)
{
	return aw::bit::trailing_zeros(value);
}
} //namespace aw::math
#endif //aw_math_bitwise_h
