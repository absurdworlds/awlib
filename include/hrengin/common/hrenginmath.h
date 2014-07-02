
#ifndef __HG_hrMath_H__
#define __HG_hrMath_H__

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrTypes.h>


namespace hrengin
{
namespace math
{

#ifdef PI
#undef PI
#endif

// Constants for PI.
const f32 PI		    = 3.14159265359f;

const f32 RECIPROCAL_PI	= 1.0f/PI;

const f32 HALF_PI	    = PI/2.0f;
const f32 QUARTER_PI	= PI/4.0f;

const f32 DOUBLE_PI     = PI*2.0f;

#ifdef PI64
#undef PI64
#endif

// Constants for 64bit PI.
const f64 PI64		        = 3.1415926535897932384626433832795028841971693993751;

const f32 RECIPROCAL_PI64	= 1.0/PI64;

const f32 HALF_PI64	        = PI64/2.0;
const f32 QUARTER_PI64	    = PI64/4.0;

const f32 DOUBLE_PI64       = PI64*2.0;

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
FORCEINLINE f64 inverseSqrt(const f64 x)
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

} //namespace math
} //namespace hrengin

#endif //__HG_hrMath_H__