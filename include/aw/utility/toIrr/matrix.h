/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ToIrr_Matrix_
#define _aw_ToIrr_Matrix_
#include <irrlicht/matrix4.h>
#include <aw/math/Matrix4.h>

namespace aw {
inline Matrix4<f32> toAW(irr::core::matrix4 const& mat)
{
	Matrix4<f32> const awMatrix(
		mat[0], mat[4], - mat[8], mat[12],
		mat[1], mat[5], - mat[9], mat[13],
		mat[2], mat[6], -mat[10], mat[14],
		mat[3], mat[7], -mat[11], mat[15]);
	return awMatrix;
}

inline irr::core::matrix4 toIrr(Matrix4<f32> const& awMatrix)
{
	irr::core::matrix4 irrMatrix;
	irrMatrix[0]  =  awMatrix[0][0];
	irrMatrix[1]  =  awMatrix[0][1];
	irrMatrix[2]  =  awMatrix[0][2];
	irrMatrix[3]  =  awMatrix[0][3];
	irrMatrix[4]  =  awMatrix[1][0];
	irrMatrix[5]  =  awMatrix[1][1];
	irrMatrix[6]  =  awMatrix[1][2];
	irrMatrix[7]  =  awMatrix[1][3];
	irrMatrix[8]  = -awMatrix[2][0];
	irrMatrix[9]  = -awMatrix[2][1];
	irrMatrix[10] = -awMatrix[2][2];
	irrMatrix[11] = -awMatrix[2][3];
	irrMatrix[12] =  awMatrix[3][0];
	irrMatrix[13] =  awMatrix[3][1];
	irrMatrix[14] =  awMatrix[3][2];
	irrMatrix[15] =  awMatrix[3][3];
	return irrMatrix;
}

} // namespace aw
#endif//_aw_ToIrr_Matrix_
