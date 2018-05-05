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
/*!
 * Signum function.
 * Returns value \a x divided by it's modulo if \a x ≠ 0, and zero otherwise.
 */
template <typename T>
constexpr T sign(T x)
{
	T o = T{0};
	if constexpr(is_signed<T>)
		return T( o < x ) - T( x < o );
	return T( o < x );
}

using std::sqrt;
using std::cbrt;
using std::fmin;
using std::fmax;
template <typename T>
auto fclamp(T value, T lower, T upper) -> enable_if<is_float<T>, T>
{
	return fmax(lower, fmin(value, upper));
}

/*!
 * Linearly interpolate two values \a v0 and \a v1.
 * The parameter \a t (within range [0,1]) specifies how close
 * the output is to one of inputs. For example:
 * `t = 0.0` produces output equal to \a v0;
 * `t = 0.5` produces the arithmetic average of input values;
 * `t = 1.0` produces output equal to \a v1.
 */
template<typename T>
constexpr T lerp(T const& v0, T const& v1, double t)
{
	return (1.0 - t)*v0 + t*v1;
}

//! Divide two integers, rounding result to the nearest value
template<typename T, typename U>
constexpr T div_round(T v, U d)
{
	U d_h = d/2;
	if constexpr(is_signed<T>)
		d_h *= (v < 0) ? -1 : 1;
	return (v + d_h) / d;
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
auto remainder(T x, U y) -> T
{
	using C = common_type<T,U>;

	auto extra = (x + y/2);
	if constexpr(std::is_floating_point_v< C >)
		// TODO: edge cases?
		extra = std::floor( extra / y ) * y;
	if constexpr(std::is_integral_v< C >)
		extra = div_floor( extra, y ) * y;
	return x - extra;
}

} //namespace math
} //namespace aw
#endif//aw_math_math_h
