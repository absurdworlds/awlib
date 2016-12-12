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
#include <aw/types/traits/common_type.h>
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
constexpr auto div_round(T v, T d) -> enable_if<is_signed<T>, T>
{
	return (v > 0) ?
	     (v + (d/2)) / d :
	     (v - (d/2)) / d;
}

template<typename T, typename U>
constexpr auto div_round(T v, U d) -> enable_if<is_unsigned<T>, T>
{
	return (v + (d/2)) / d;
}


namespace _impl {
template<typename T, typename U>
constexpr auto was_rounded_up(T r, U d)
{
	return (r != 0) && ((r < 0) != (d < 0));
}
} // namespace _impl

//! Divide two integers, rounding result towards negative infinity
template<typename T, typename U>
constexpr auto div_floor(T v, U d) -> enable_if<is_signed<T>, T>
{
	T q = v / d;
	T r = v % d;
	if ( _impl::was_rounded_up( r, d ) )
		--q;
	return q;
}

template<typename T, typename U>
constexpr auto div_floor(T v, U d) -> enable_if<is_unsigned<T>, T>
{
	return v / d;
}

//! Remainder of div_floor
template<typename T, typename U>
constexpr auto mod_floor(T v, U d)
{
	T r = v % d;
	if ( _impl::was_rounded_up( r, d ) )
		r += d;
	return r;
}

template<typename T, typename U>
auto remainder(T x, U y) -> require<common_type<T,U>, std::is_floating_point>
{
	// TODO: edge cases?
	return x - std::floor( (x + y/2) / y ) * y;
}

template<typename T, typename U>
constexpr auto remainder(T x, U y) -> require<common_type<T,U>, std::is_integral>
{
	return x - div_floor( (x + y/2) , y ) * y;
}

} //namespace math
} //namespace aw
#endif//aw_math_math_h
