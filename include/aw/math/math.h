/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_math_
#define _aw_math_
#include <cmath>
#include <cassert>
#include <cstdlib>

#include <type_traits>
#include <algorithm>

#include <aw/config.h>
#include <aw/types/types.h>

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


//! Calculate square root of a number
inline f32 sqrt(f32 const x)
{
	return ::sqrtf(x);
}

//! Calculate square root of a number
inline f64 sqrt(f64 const x)
{
	return ::sqrt(x);
}

//! Calculate square root of an integer
inline i32 sqrt(i32 const x)
{
	return static_cast<i32>(::sqrt(static_cast<f32>(x)));
}

//! Calculate inverse square root of a double
inline f64 invSqrt(const f64 x)
{
	return 1.0 / sqrt(x);
}

template <typename T>
inline T clamp(T value, T lower, T upper)
{
	return std::min(upper, std::max(value, lower));
}

template <>
inline f32 clamp(f32 value, f32 lower, f32 upper)
{
	return fminf(lower, fmaxf(value, upper));
}

template <>
inline f64 clamp(f64 value, f64 lower, f64 upper)
{
	return fmin(lower, fmax(value, upper));
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
} //namespace math
} //namespace aw
#endif //_aw_math_
