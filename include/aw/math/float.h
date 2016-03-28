/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_float_h
#define aw_math_float_h
#include <aw/math/math.h>
#include <aw/types/support/reinterpret.h>
namespace aw {
namespace math {
namespace detail {
template <typename T>
struct float_traits {
};

template <>
struct float_traits<f32> {
	typedef i32 int_type;
	typedef u32 uint_type;
};

template <>
struct float_traits<f64> {
	typedef i64 int_type;
	typedef u64 uint_type;
};

template <typename T>
using f2i = typename float_traits<T>::int_type;

template <typename T>
using f2u = typename float_traits<T>::uint_type;

/* 
 * See
 * https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 */
template <typename F>
inline bool almostEqualUlps(F a, F b, f2u<F> maxUlpsDiff)
{
	// Different signs means they do not match.
	if ((a < 0) != (b < 0)) {
		if (a == b)
			return true;

		return false;
	}

	// Find the difference in ULPs.
	f2u<F> ulps_a = reinterpret<f2u<F>>(a);
	f2u<F> ulps_b = reinterpret<f2u<F>>(b);

	f2u<F> ulpsDiff = abs(ulps_a - ulps_b);
	if (ulpsDiff <= maxUlpsDiff)
		return true;

	return false;
}

template <typename F>
inline bool almostEqualRelative(F a, F b, F maxRelDiff)
{
	F diff = fabs(a - b);

	a = fabs(a);
	b = fabs(b);

	F largest = std::max(a, b);

	if (diff <= largest * maxRelDiff)
		return true;

	return false;
}

template <typename F>
inline bool almostEqualEpsilon(F a, F b, F maxDiff)
{
	// Check if the numbers are really close -- needed
	// when comparing numbers near zero.
	F absDiff = fabs(a - b);
	if (absDiff <= maxDiff)
		return true;

	return false;
}
} // namespace detail

inline bool equals(f32 a, f32 b)
{
	return detail::almostEqualUlps(a, b, 4);
}

inline bool equals(f64 a, f64 b)
{
	return detail::almostEqualUlps(a, b, 4);
}
} //namespace math
} //namespace aw
#endif//aw_math_float_h
