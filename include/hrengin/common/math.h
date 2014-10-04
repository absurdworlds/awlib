/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_math_
#define _hrengin_math_

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include <algorithm>

#include <hrengin/common/macro.h>
#include <hrengin/common/types.h>


namespace hrengin {
namespace math {

//! PI mathematical constant
f32 const PI	= 3.14159265359f;
//! E mathematical constant
f32 const E	= 2.71828182845f;

f32 const RECIPROCAL_PI	= 1.0f/PI;

f32 const HALF_PI	= PI/2.0f;
f32 const QUARTER_PI	= PI/4.0f;

f32 const DOUBLE_PI	= PI*2.0f;

//! 64-bit wide PI
f64 const PI64	= 3.14159265358979323846; //26433832795028841971693993751;
//! 64-bit wide E
f64 const E64	= 2.71828182845904523536; //02874713526624977572470936999595

const f64 RECIPROCAL_PI64	= 1.0/PI64;

const f64 HALF_PI64		= PI64/2.0;
const f64 QUARTER_PI64		= PI64/4.0;

const f64 DOUBLE_PI64		= PI64*2.0;

// 32bit Constant for converting from degrees to radians
const f32 DEGTORAD = PI / 180.0f;

// 32bit constant for converting from radians to degrees
const f32 RADTODEG   = 180.0f / PI;

// 64bit constant for converting from degrees to radians
const f64 DEGTORAD64 = PI64 / 180.0;

// 64bit constant for converting from radians to degrees
const f64 RADTODEG64 = 180.0 / PI64;


const i32 ROUNDING_ERROR_INT = 0;
const f32 ROUNDING_ERROR_float32 = 0.000001f;
const f64 ROUNDING_ERROR_float64 = 0.00000001;

// Calculates square root of a number
FORCEINLINE f32 sqrt(const f32 x)
{
	return ::sqrtf(x);
}

FORCEINLINE f64 sqrt(const f64 x)
{
	return ::sqrt(x);
}

// Calculates square root of an integer
FORCEINLINE i32 sqrt(const i32 x)
{
	return static_cast<i32>(::sqrt(static_cast<f32>(x)));
}

// Calculates inverse square root of a double
FORCEINLINE f64 invSqrt(const f64 x)
{
	return 1.0 / sqrt(x);
}

FORCEINLINE bool equals(const i32 a, const i32 b, const i32 tolerance = ROUNDING_ERROR_INT)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

FORCEINLINE bool equals(const u32 a, const u32 b, const u32 tolerance = ROUNDING_ERROR_INT)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

FORCEINLINE bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_float32)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

FORCEINLINE bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_float64)
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

/*!
   Normalize angle between -180 and 180 degrees
   \param angle
      angle to normalize, in degrees
   \return
      input angle normalized to (-180;180] range
 */
inline f32 normalizeAngle(f32 angle)
{
	angle = fmod(angle, 360.0f);
	return    angle >   180.0f ? angle - 360.0f
		: angle <= -180.0f ? angle + 360.0f 
		: angle;
}

/*! Shorthand for above function */
inline f32 wrapAngle(f32 angle)
{
	return normalizeAngle(angle);
}

/*!
   Normalize angle between -Pi and Pi radians
   \param angle Value in radians to normalize
   \return Angle in (-Pi;Pi] range
 */
inline f32 wrapAngleRad(f32 angle)
{
	angle = fmod(f64(angle), DOUBLE_PI64);
	return    angle >   PI64 ? angle - DOUBLE_PI64
		: angle <= -PI64 ? angle + DOUBLE_PI64 
		: angle;
}

//! Interpolate values v0 and v1 by parameter t
inline f32 lerp(f32 v0, f32 v1, f64 t)
{
	return (1-t)*v0 + t*v1;
}

//! Check if value is a power of 2
inline bool isPowerOf2(u32 value)
{
	return (value & (value - 1)) && value;
}

//! Truncate integer to 8 bits
template<typename integer_type>
inline u8 mask8(integer_type val)
{
	return u8(val & 0xFF);
}

//! Truncate integer to 16 bits
template<typename integer_type>
inline u16 mask16(integer_type val)
{
	return u16(val & 0xFFFF);
}

//! Truncate integer to 32 bits
template<typename integer_type>
inline u32 mask32(integer_type val)
{
	return u32(val & 0xFFFFFFFF);
}

} //namespace math
} //namespace hrengin

#endif //_hrengin_math_
