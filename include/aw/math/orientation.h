/*
 * Copyright (C) 2018  hedede <haddayn@gmail.com>
 * Copyright (C) 2018  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_polar_h
#define aw_math_polar_h
#include <aw/math/trigonometry.h>
#include <aw/math/vector3d.h>
#include <aw/math/matrix4.h>
namespace aw::math {
/*!
 * Convert spherical coordinates into cartesian coordiantes.
 *
 * See following illustration:
 *       y |    r
 *         |   /
 *         |--/
 *         |φ/
 *         |/__________ x
 *        /θ\
 *       /---\
 *      /     \
 *   z /       r
 */
template<typename T, typename P>
vector3d<T> spherical_to_cartesian(T r, angle<T,P> phi, angle<T,P> theta)
{
	auto sp = sin( phi );
	auto cp = cos( phi );
	auto st = sin( theta );
	auto ct = cos( theta );

	auto x = r * sp * st;
	auto y = r * cp;
	auto z = r * sp * ct;

	return {x,y,z};
}

inline namespace rh {
template<typename T>
matrix3<T> look_at_inverse(vector3d<T> forward, vector3d<T> up = {0,1,0})
{
	forward = -forward.normalize();
	auto right   = cross(up,forward).normalize();
	up           = cross(forward,right);

	matrix3<T> rot{ right, up, forward };
	return rot;
}

/*!
 * Compute matrix which orients an object in such way,
 * that it faces in direction \a forward.
 *
 * \up is a vector perpendicular to the Z axis.
 * \a forward must not be same as \a up.
 */
template<typename T>
matrix3<T> look_at(vector3d<T> forward, vector3d<T> up = {0,1,0})
{
	return transpose(look_at_inverse(forward,up));
}

/*!
 * Compute matrix which translates an object into position \a from,
 * and orients it to ‘look’ at point \a to.
 */
template<typename T>
matrix4<T> look_at(vector3d<T> from, vector3d<T> to, vector3d<T> up)
{
	auto trs = expand_matrix( look_at(to - from, up) );
	trs[0][3] = from[0];
	trs[1][3] = from[1];
	trs[2][3] = from[2];
	return trs;
}
} //inline namespace rh
} // namespace aw::math
#endif//aw_math_polar_h
