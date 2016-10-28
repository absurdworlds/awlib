/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2016 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_constants_h
#define aw_math_constants_h
#include <aw/types/types.h>

namespace aw {
namespace math {
//! π (mathematical constant)
f64 const pi = 3.14159265358979323846; //26433832795028841971693993751;
//! e (mathematical constant)
f64 const e  = 2.71828182845904523536; //02874713526624977572470936999;

f64 const reciprocal_pi = 1.0/pi;

f64 const half_pi       = pi/2.0;
f64 const quarter_pi    = pi/4.0;

f64 const double_pi     = 2.0*pi;
} //namespace math
} //namespace aw
#endif //aw_math_constants_h
