/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#ifndef _hrengin_CPhysicsBody_
#define _hrengin_CPhysicsBody_

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/types.h>
#include <hrengin/game/IBaseEntity.h>
#include <hrengin/physics/IPhysicsBody.h>
//#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
namespace physics {

class CPhysicsBody : public IPhysicsBody {
public:
	CPhysicsBody(btCollisionObject* pCollObject);
	CPhysicsBody(btCollisionObject* pCollObject, IBaseEntity* pAttach);

	virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
	virtual IBaseEntity* getEntity();;

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

	virtual Vector3d<f32> getPosition();
	virtual Vector3d<f32> getRotation();

protected:
	IBaseEntity* AttachedTo;
	btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//_hrengin_CPhysicsBody_