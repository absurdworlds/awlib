#ifndef __HRENGIN_ToBullet__
#define __HRENGIN_ToBullet__

#include <hrengin/common/Vector3d.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

namespace hrengin {
namespace physics {

inline Vector3d<f32> btVectorToHrg(btVector3 btVec) 
{
	return Vector3d(btVec[0], btVec[1], btVec[2]);
}

inline btVector3 hrgVectorToBt(Vector3d<f32> hrgVec) 
{
	return btVector3(hrgVec.X, hrgVec.Y, hrgVec.Z);
}

}
}

#endif //__HRENGIN_ToBullet__