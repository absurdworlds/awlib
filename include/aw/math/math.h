/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_math_h
#define aw_math_math_h
#include <cmath>
#include <cassert>
#include <cstdlib>

#include <algorithm>

#include <aw/config.h>
#include <aw/types/types.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>

namespace aw {
namespace math {
namespace _impl {
template <typename T>
constexpr T sign(T x, std::false_type)
{
	return T{0} < x;
}

template <typename T>
constexpr T sign(T x, std::true_type)
{
	return (T{0} < x) - (x < T{0});
}
} // namespace _impl

template <typename T>
constexpr T sign(T x)
{
	return _impl::sign(x, std::is_signed<T>());
}

using std::sqrt;
using std::fmin;
using std::fmax;
template <typename T>
auto fclamp(T value, T lower, T upper) -> enable_if<is_float<T>, T>
{
	return fmax(lower, fmin(value, upper));
}

/*! Interpolate two values
 *      \param v0 First value to interpolate
 *      \param v1 Second value to interpolate
 *      \param t  Interpolation parameter
 *      Must be in range [0,1].
 *      \return Interpolated vector
 */
template<typename T>
T lerp(T const& v0, T const& v1, f64 t)
{
	return (1.0 - t)*v0 + t*v1;
}

//! Divide two integers, rounding result to nearest value
template<typename T>
constexpr auto div_round(T v, T d) -> enable_if<is_int<T>, T>
{
	return (v + (d/2)) / d;
}

template<typename T>
auto remainder(T x, T y) -> enable_if<is_float<T>, T>
{
	return std::remainder( x, y );
}

template<typename T>
constexpr auto remainder(T x, T y) -> enable_if<is_int<T>, T>
{
	return x - div_round(x, y) * y;
}

} //namespace math
} //namespace aw
#endif//aw_math_math_h
