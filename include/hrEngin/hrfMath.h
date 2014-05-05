

#ifndef __HR_F_MATH_H__
#define __HR_F_MATH_H__

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

#include "hrtype.h"

namespace hrengin
{
	
namespace math
{

	// returns if a equals b, taking an explicit rounding tolerance into account
	// using implementation from Irrlicht

	const int32 ROUNDING_ERROR_INT = 0;
	const float32 ROUNDING_ERROR_float32 = 0.000001f;
	const float64 ROUNDING_ERROR_float64 = 0.00000001;

	inline bool equals(const int32 a, const int32 b, const int32 tolerance = ROUNDING_ERROR_INT)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	inline bool equals(const uint32 a, const uint32 b, const uint32 tolerance = ROUNDING_ERROR_INT)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}
			
	inline bool equals(const float32 a, const float32 b, const float32 tolerance = ROUNDING_ERROR_float32)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}

	inline bool equals(const float64 a, const float64 b, const float64 tolerance = ROUNDING_ERROR_float64)
	{
		return (a + tolerance >= b) && (a - tolerance <= b);
	}
}
}

#endif//__HR_F_MATH_H__