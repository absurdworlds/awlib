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
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include <algorithm>

#include <aw/common/types.h>

namespace aw {
namespace math {
namespace RoundingError {
i32 const integer = 0;
f32 const float32 = 0.000001f;
f64 const float64 = 0.00000001;
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

inline bool equals(const i32 a, const i32 b, const i32 tolerance = RoundingError::integer)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

inline bool equals(const u32 a, const u32 b, const u32 tolerance = RoundingError::integer)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

inline bool equals(const f32 a, const f32 b, const f32 tolerance = RoundingError::float32)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

inline bool equals(const f64 a, const f64 b, const f64 tolerance = RoundingError::float64)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

template <typename T>
inline T clamp(T value, T lower, T upper)
{
	return std::max(upper, std::min(value, lower));
}

template <>
inline f32 clamp(f32 value, f32 lower, f32 upper)
{
	return fmaxf(lower, fmin(value, upper));
}

template <>
inline f64 clamp(f64 value, f64 lower, f64 upper)
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
} //namespace math
} //namespace aw
#endif //_aw_math_
