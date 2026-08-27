/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_numeric_h
#define aw_math_numeric_h
#include <limits>
#include <aw/bit/mask.h>
#include <aw/types/types.h>
namespace aw {
//! Number of radix digits in type T
template<typename T>
constexpr size_t num_digits = std::numeric_limits<T>::digits;

//! Wrapper for (x % 2) check
template<typename T>
constexpr bool is_odd(T value)
{
	return value & 1;
}

//! Wrapper for (x % 2 == 0) check
template<typename T>
constexpr bool is_even(T value)
{
	return !is_odd(value);
}

// XXX: temporary until C++17 is around
constexpr intmax_t gcd(intmax_t x, intmax_t y)
{
	if (y == 0)
		return x == 0 ? 1 : x;
	return gcd(y, x % y);
}

constexpr intmax_t lcm(intmax_t x, intmax_t y)
{
	return x / gcd(x,y) * y;
}

namespace math {
//! Compute log2 of an integer value
template <typename Int>
constexpr size_t log2(Int value)
{
	static_assert(num_digits<Int> <= num_digits<u64>, "Type is too large.");
	constexpr u64 powers[] = { 0, 1, 2, 4, 8, 16, 32 };
	constexpr u64 lookup[] = {
	       0,
	       bit::upper_mask<u64>(1),  bit::upper_mask<u64>(2),
	       bit::upper_mask<u64>(4),  bit::upper_mask<u64>(8),
	       bit::upper_mask<u64>(16), bit::upper_mask<u64>(32)
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

/*! Check if value is a power of 2 */
template <typename Int>
constexpr bool is_power_of_2(Int value)
{
	return value && !(value & (value - 1));
}
} // namespace math
} //namespace aw
#endif //aw_math_numeric_h
