/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_PhysicsWorld_
#define _awrts_PhysicsWorld_

#include <awrts/common/types.h>
#include <awrts/common/hidden_impl.h>

#include <awrts/math/Vector3d.h>

#include <awrts/physics/DebugDrawer.h>
#include <awrts/physics/CollisionFilter.h>
#include <awrts/physics/RayResultCallback.h>

namespace awrts {
namespace physics {

class CollisionObject;
class CollisionPhantom;
class RigidBody;

/*!
 * This class is responsible for collision detection,
 * dynamics simulation et cetera
 */
class PhysicsWorld {
public:
	virtual ~PhysicsWorld() {};

	/*!
	 * Insert a rigid body into world
	 */
	virtual void addBody(RigidBody* body) = 0;
	virtual void addBody(RigidBody* body, CollisionFilter filter) = 0;
	virtual void addObject(CollisionObject* object) = 0;
	virtual void addObject(CollisionObject* object, CollisionFilter filter) = 0;

	virtual void removeBody(RigidBody* body) = 0;
	virtual void removeObject(CollisionObject* object) = 0;

	//TODO: virtual DebugDrawer* createDebugDrawer();
	// this will allow to remove at least DebugDrawer's 'hidden details'
	virtual void setDebugDrawer(DebugDrawer* drawer) = 0;

	virtual void castRay(Vector3d<f32> from, Vector3d<f32> to, RayResultCallback* callback) = 0;

	/*!
	 * Step the simulation
	 */
	virtual bool step() = 0;

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(PhysicsWorld);
};

} // namespace physics
} // namespace awrts
#endif//_awrts_PhysicsWorld_
