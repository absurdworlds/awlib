/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_math_constants
#define _aw_math_constants
#include <aw/common/types.h>

namespace aw {
namespace math {
//! π (mathematical constant)
f64 const Pi	= 3.14159265358979323846; //26433832795028841971693993751;
//! e (mathematical constant)
f64 const e	= 2.71828182845904523536; //02874713526624977572470936999595

f64 const ReciprocalPi	= 1.0/Pi;
 
f64 const HalfPi		= Pi/2.0;
f64 const QuarterPi		= Pi/4.0;
          
f64 const DoublePi		= Pi*2.0;

// Constant defining ratio of degrees to radians
f64 const DegreesInRadian = 180.0 / Pi;

// Constant defining ratio of radians to degrees
f64 const RadiansInDegree = Pi / 180.0;
} //namespace math
} //namespace aw
#endif //_aw_math_constants
