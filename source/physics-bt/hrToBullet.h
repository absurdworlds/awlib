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

inline Vector3d<f32> toHrengin(btVector3 const& btVec)
{
	return Vector3d<f32>(btVec[0], btVec[1], btVec[2]);
}

inline btVector3 toBullet(Vector3d<f32> const& hrVec)
{
	return btVector3(hrVec.X, hrVec.Y, hrVec.Z);
}

void quaternionToEuler(btQuaternion const& quat, btVector3& euler);

} // namespace physics
} // namespace hrengin

#endif //_hrengin_hrToBullet_
