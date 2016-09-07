/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix4_h
#define aw_math_matrix4_h
#include <aw/math/vector4d.h>
#include <aw/math/matrix3.h>
namespace aw {
namespace math {
template<typename T>
using matrix4 = matrix<T,4,4>;

//! Extract translation from matrix
template<typename T>
vector3d<T> translation(matrix4<T> const& mat)
{
	return { get<3,0>(mat), get<3,1>(mat), get<3,2>(mat) };
}

//! Extract scale from matrix
template<typename T>
vector3d<T> scale(matrix4<T> const& mat)
{
	return scale( sub_matrix<3,3>(mat) );
}

//! Extract scale, assuming it is positive
template<typename T>
vector3d<T> scalePositive(matrix4<T> const& mat)
{
	vector3d<T> const row1 = sub<3>( row<0>(mat) );
	vector3d<T> const row2 = sub<3>( row<1>(mat) );
	vector3d<T> const row3 = sub<3>( row<2>(mat) );

	T const scaleX = row1.length();
	T const scaleY = row2.length();
	T const scaleZ = row3.length();

	return { scaleX, scaleY, scaleZ };
}

/*! Get rotation in radians
 *  \param scale Scales on X, Y, Z axes, obtained through getScale()
 *  \return Vector consisting of euler angles (in radians)
 */
template<typename T>
vector3d<T> rotation(matrix4<T> const& mat, vector3d<T> const& scale)
{
	vector3d<T> rot;

	rot.y = asin(-get<2,0>(mat));

	T const test = T(1.0 /*- math::RoundingError::float64*/);

	if (rot.y >= test || rot.y <= -test) {
		rot.x = atan2(get<2,1>(mat)*scale[2], get<2,2>(mat));
		rot.z = atan2(get<1,0>(mat)*scale[0], get<0,0>(mat));
	} else {
		rot.x = T(0.0);
		rot.z = atan2(get<0,1>(mat)*scale[1], get<1,1>(mat));
	}

	return rot;
}

/*! Get rotation in radians, calculating the scale
 *  \return Vector consisting of euler angles (in radians)
 */
template<typename T>
vector3d<T> rotation(matrix4<T> const& mat)
{
	return rotation(mat, scale(mat));
}

/*! Get rotation in radians, assuming that matrix is not scaled
 *  \return Vector consisting of euler angles (in radians)
 */
template<typename T>
vector3d<T> rotationUnscaled(matrix4<T> const& mat)
{
	static vector3d<T> const scale = {1, 1, 1};
	return rotation(mat, scale);
}
} // namespace math
} // namespace aw
#endif //aw_math_matrix4_h
