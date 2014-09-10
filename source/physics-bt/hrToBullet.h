/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#ifndef _hrengin_hrToBullet_
#define _hrengin_hrToBullet_

#include <hrengin/common/Vector3d.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

namespace hrengin {
namespace physics {

inline Vector3d<f32> toHrengin(btVector3 btVec) 
{
	return Vector3d<f32>(btVec[0], btVec[1], btVec[2]);
}

inline btVector3 toBullet(Vector3d<f32> hrVec) 
{
	return btVector3(hrVec.X, hrVec.Y, hrVec.Z);
}

inline void quaternionToEuler(const btQuaternion &quat, btVector3 &euler) {
	btScalar W = quat.getW();
	btScalar X = quat.getX();
	btScalar Y = quat.getY();
	btScalar Z = quat.getZ();
	float WSquared = W * W;
	float XSquared = X * X;
	float YSquared = Y * Y;
	float ZSquared = Z * Z;

	euler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
	euler.setY(asinf(-2.0f * (X * Z - Y * W)));
	euler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
	euler *= math::RADTODEG;
}


} // namespace physics
} // namespace hrengin

#endif //_hrengin_hrToBullet_
