/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CollisionPhantom_impl_
#define _aw_CollisionPhantom_impl_
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/common/types.h>
#include <awrts/game/Entity.h>
#include <aw/physics/CollisionPhantom.h>
//#include <aw/physics/PhysicsManager.h>

#include "CollisionObject.h"

namespace aw {
namespace physics {
namespace bullet {

class CollisionPhantom : public physics::CollisionPhantom {
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
} // namespace bullet
} // namespace physics
} // namespace aw
#endif//_aw_CollisionPhantom_impl_
