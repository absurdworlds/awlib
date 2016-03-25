/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Vector2d_h
#define aw_Vector2d_h
#include <aw/math/Vector.h>
namespace aw {
//! Geometric object characterized by magnitude and direction
template<typename T>
using Vector2d = Vector<T,2>;

//! Calculates angle of the vector
template<typename T>
T angle(Vector2d<T> const& vec)
{
	T yaw = T(atan2(f64(vec[Vec::X]), f64(vec[Vec::Y])));

	if (yaw <= -math::Pi) {
		yaw += math::DoublePi;
	} else if (yaw > math::Pi) {
		yaw -= math::DoublePi;
	}

	return math::radToDeg(yaw);
}
} // namespace aw
#endif//aw_Vector2d_h
