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
#include <aw/math/float.h>
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
	return { get<0,3>(mat), get<1,3>(mat), get<2,3>(mat) };
}

//! Extract scale from matrix
template<typename T>
vector3d<T> scale(matrix4<T> const& mat)
{
	return scale( sub_matrix<3,3>(mat) );
}

//! Extract scale, assuming it is positive
template<typename T>
vector3d<T> scale_positive(matrix4<T> const& mat)
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
 *  \param scale Scales on X, Y, Z axes, obtained through scale_positive()
 *  \return Vector of euler angles (in radians), holding the rotation
 *          around X (pitch) in its x component, around Y (yaw) in y and
 *          around Z (roll) in z — the layout `matrix_from_euler` takes.
 */
template<typename T>
vector3d<T> rotation(matrix4<T> const& mat, vector3d<T> const& scale)
{
	/*
	 * The scale sits on the rows (see scale_positive), so dividing each
	 * row by it leaves a pure rotation to read the angles off.
	 */
	auto const m = [&mat, &scale] (size_t i, size_t j) {
		return mat.get(i, j) / scale[i];
	};

	T const sin_yaw = math::fclamp(-m(2,0), T{-1}, T{1});

	vector3d<T> rot = {};

	/*
	 * At |yaw| = 90° the X and Z axes coincide and only (pitch − roll)
	 * is determined; hand the whole of it to pitch.
	 *
	 * The cutoff is the machine epsilon, not the much looser
	 * float_traits::epsilon: the general path holds up until sin(yaw)
	 * stops being distinguishable from 1, and switching any earlier
	 * only snaps yaw to 90° when it demonstrably is not.
	 */
	constexpr T threshold = T(1) - float_traits<T>::max_rel;

	if (sin_yaw > threshold || sin_yaw < -threshold) {
		rot[axis::x] = T(std::atan2(sin_yaw * m(0,1), m(1,1)));
		rot[axis::y] = T(std::copysign(pi/2, sin_yaw));
		rot[axis::z] = T{0};
	} else {
		rot[axis::x] = T(std::atan2(m(2,1), m(2,2)));
		rot[axis::y] = T(std::asin(sin_yaw));
		rot[axis::z] = T(std::atan2(m(1,0), m(0,0)));
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
vector3d<T> rotation_unscaled(matrix4<T> const& mat)
{
	static vector3d<T> const scale = {1, 1, 1};
	return rotation(mat, scale);
}
} // namespace math
} // namespace aw
#endif //aw_math_matrix4_h
