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

} // namespace aw::math
#endif//aw_math_polar_h
