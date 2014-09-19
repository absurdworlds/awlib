/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#ifndef _hrengin_CRigidBody_
#define _hrengin_CRigidBody_

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/types.h>
#include <hrengin/game/IBaseEntity.h>
#include <hrengin/physics/IRigidBody.h>
//#include <hrengin/physics/IPhysicsManager.h>

#include "CCollisionObject.h"

namespace hrengin {
namespace physics {

class CRigidBody : public IRigidBody {
public:
	CRigidBody(btRigidBody* body);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

	virtual Vector3d<f32> getPosition() const;
	virtual Vector3d<f32> getRotation() const;

	virtual ICollisionObject::Details* getDetails()
	{
		return &details_;
	}
protected:
	ICollisionObject::Details details_;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_CRigidBody_
