/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector2d_h
#define aw_math_vector2d_h
#include <aw/math/vector.h>
namespace aw {
namespace math {
//! Geometric object characterized by magnitude and direction
template<typename T>
using vector2d = vector<T,2>;

//! Calculates angle of the vector
template<typename T>
T angle(vector2d<T> const& vec)
{
	T yaw = T(atan2(f64(vec[axis::x]), f64(vec[axis::y])));

	if (yaw <= -math::pi) {
		yaw += math::double_pi;
	} else if (yaw > math::pi) {
		yaw -= math::double_pi;
	}

	return math::radToDeg(yaw);
}
} // namespace math
} // namespace aw
#endif//aw_math_vector2d_h
