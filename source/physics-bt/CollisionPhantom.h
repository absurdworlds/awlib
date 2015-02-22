/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CollisionPhantom_
#define _hrengin_CollisionPhantom_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/types.h>
#include <hrengin/game/Entity.h>
#include <hrengin/physics/CollisionPhantom.h>
//#include <hrengin/physics/PhysicsManager.h>

#include "CollisionObject.h"

namespace hrengin {
namespace physics {

class CollisionPhantom : public CollisionPhantom {
public:
	CollisionPhantom(btCollisionObject* object);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

	virtual Vector3d<f32> getPosition() const;
	virtual Vector3d<f32> getRotation() const;

	virtual CollisionObject::Details* getDetails()
	{
		return &details_;
	}
protected:
	CollisionObject::Details details_;
};

} // namespace physics
} // namespace hrengin
#endif//_hrengin_CollisionPhantom_
