/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_Matrix4_h
#define aw_math_Matrix4_h
#include <aw/math/Vector3d.h>
#include <aw/math/Vector4d.h>
#include <aw/math/Matrix3.h>
namespace aw {
template<typename T>
using Matrix4 = Matrix<T,4,4>;

//! Extract translation from matrix
template<typename T>
Vector3d<T> translation(Matrix4<T> const& mat)
{
	return { get<3,0>(mat), get<3,1>(mat), get<3,2>(mat) };
}

//! Extract scale from matrix
template<typename T>
Vector3d<T> scale(Matrix4<T> const& mat)
{
	return scale( subMatrix<3,3>(mat) );
}

//! Extract scale, assuming it is positive
template<typename T>
Vector3d<T> scalePositive(Matrix4<T> const& mat)
{
	Vector3d<T> const row1 = sub<3>( row<0>(mat) );
	Vector3d<T> const row2 = sub<3>( row<1>(mat) );
	Vector3d<T> const row3 = sub<3>( row<2>(mat) );

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
Vector3d<T> rotation(Matrix4<T> const& mat, Vector3d<T> const& scale)
{
	Vector3d<T> rot;

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
Vector3d<T> rotation(Matrix4<T> const& mat)
{
	return rotation(mat, scale(mat));
}

/*! Get rotation in radians, assuming that matrix is not scaled
 *  \return Vector consisting of euler angles (in radians)
 */
template<typename T>
Vector3d<T> rotationUnscaled(Matrix4<T> const& mat)
{
	static Vector3d<T> const scale = {1, 1, 1};
	return rotation(mat, scale);
}
} // namespace aw
#endif //_aw_Matrix4_
