/*
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_vector3d_h
#define aw_math_vector3d_h
#include <aw/math/vector2d.h>
namespace aw {
namespace math {
//! Vector in 3D space
template<typename T>
using vector3d = vector<T,3>;

/*!
 * Calculate cross-product of two 3D vectors
 */
template<typename T>
vector3d<T> cross(vector3d<T> const& vec1, vector3d<T> const& vec2)
{
	T const cx = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	T const cy = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	T const cz = vec1[0] * vec2[1] - vec1[1] * vec2[0];
	return {cx, cy, cz};
}

/*!
 * Get rotation around Y axis
 */
template<typename T>
T yaw(vector3d<T> const& vec)
{
	T yaw = T(atan2(f64(vec[axis::x]), f64(vec[axis::z])));

	if (yaw <= -math::pi) {
		yaw += 2*pi;
	} else if (yaw > math::pi) {
		yaw -= 2*pi;
	}

	return yaw;
}

/*!
 * Get rotation around X axis
 */
template<typename T>
T pitch(vector3d<T> const& vec)
{
	auto x = vec[axis::x], y = vec[axis::y], z = vec[axis::z];
	f64 const xz = math::sqrt(x*x + z*z);
	T const pitch = T(atan2(f64(xz), f64(y)) - pi/2);

	if (pitch <= -math::pi) {
		pitch += 2*pi;
	} else if (pitch >= math::pi) {
		pitch -= 2*pi;
	}

	return pitch;
}

/*!
 * Get euler angles such that when applied to a (0,0,1) direction
 * vector would make it point in the same direction as vector \vec.
 *
 * \return
 *     A rotation vector containing the X (pitch) and Y (raw)
 *     rotations in degrees, of this vector.
 */
template<typename T>
vector2d<T> horizontal_angle(vector3d<T> const& vec)
{
	return {yaw(vec), pitch(vec)};
}
} // namespace math
} // namespace aw
#endif//aw_math_vector3d_h
