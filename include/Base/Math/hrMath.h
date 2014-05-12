
#ifndef __HG_hrMath_H__
#define __HG_hrMath_H__

#include "Base/Config/hrConfig.h"

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include "Base/hrTypes.h"


namespace hrengin
{
namespace math
{
	
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

FORCEINLINE i32 sqrt(const i32 x)
{
	return static_cast<i32>(::sqrt(static_cast<f32>(x)));
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