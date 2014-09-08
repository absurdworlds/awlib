/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#ifndef _hrengin_CPhysicsPhantom_
#define _hrengin_CPhysicsPhantom_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/types.h>
#include <hrengin/game/IBaseEntity.h>
#include <hrengin/physics/IPhysicsPhantom.h>
//#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
namespace physics {

class CPhysicsPhantom : public IPhysicsPhantom {
public:
	CPhysicsPhantom(btCollisionObject* pCollObject);
	CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach);

	virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
	virtual IBaseEntity* getEntity();

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

protected:
	IBaseEntity* AttachedTo;
	btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//_hrengin_CPhysicsPhantom_
