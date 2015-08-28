/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hrToIrr_
#define _hrengin_hrToIrr_

#include <irrlicht/vector3d.h>
#include <irrlicht/line3d.h>
#include <irrlicht/matrix4.h>

#include <hrengin/math/Vector3d.h>
#include <hrengin/math/Line3d.h>
#include <hrengin/math/Matrix4.h>

namespace hrengin {

inline Vector3d<f32> toHrengin(irr::core::vector3df const& irrVec)
{
	return Vector3d<f32>(irrVec.X, irrVec.Y, irrVec.Z);
}

inline irr::core::vector3df toIrr(Vector3d<f32> const& hrVec)
{
	return irr::core::vector3df(hrVec.x,hrVec.y,hrVec.z);
}


inline Line3d<f32> toHrengin(irr::core::line3df const& irrLine)
{
	irr::core::vector3df const& start = irrLine.start;
	irr::core::vector3df const& end = irrLine.end;
	return Line3d<f32>(start.X,start.Y,start.Z,end.X,end.Y,end.Z);
}

inline irr::core::line3df toIrr(Line3d<f32> const& hrLine)
{
	Vector3d<f32> const& start = hrLine.start;
	Vector3d<f32> const& end = hrLine.end;
	return irr::core::line3df(start.x,start.y,start.z,end.x,end.y,end.z);
}


inline Matrix4<f32> toHrengin(irr::core::matrix4 const& mat)
{
	Matrix4<f32> const hrMatrix(
		mat[0], mat[4], - mat[8], mat[12],
		mat[1], mat[5], - mat[9], mat[13],
		mat[2], mat[6], -mat[10], mat[14],
		mat[3], mat[7], -mat[11], mat[15]);
	return hrMatrix;
}

inline irr::core::matrix4 toIrr(Matrix4<f32> const& hrMatrix)
{
	irr::core::matrix4 irrMatrix;
	irrMatrix[0]  =  hrMatrix[0][0];
	irrMatrix[1]  =  hrMatrix[0][1];
	irrMatrix[2]  =  hrMatrix[0][2];
	irrMatrix[3]  =  hrMatrix[0][3];
	irrMatrix[4]  =  hrMatrix[1][0];
	irrMatrix[5]  =  hrMatrix[1][1];
	irrMatrix[6]  =  hrMatrix[1][2];
	irrMatrix[7]  =  hrMatrix[1][3];
	irrMatrix[8]  = -hrMatrix[2][0];
	irrMatrix[9]  = -hrMatrix[2][1];
	irrMatrix[10] = -hrMatrix[2][2];
	irrMatrix[11] = -hrMatrix[2][3];
	irrMatrix[12] =  hrMatrix[3][0];
	irrMatrix[13] =  hrMatrix[3][1];
	irrMatrix[14] =  hrMatrix[3][2];
	irrMatrix[15] =  hrMatrix[3][3];
	return irrMatrix;
}

} // namespace hrengin
#endif//_hrengin_hrToIrr_
