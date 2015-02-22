/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_PhysicsWorld_impl_
#define _hrengin_PhysicsWorld_impl_
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/physics/PhysicsManager.h>
#include <hrengin/physics/DebugDrawer.h>
#include <hrengin/physics/PhysicsWorld.h>

namespace hrengin {
namespace physics {
// FIXME!!!!
class PhysicsWorld::Details {
public:
	btDynamicsWorld* world;
};

namespace bullet {
class PhysicsWorld : public physics::PhysicsWorld {
public:
	PhysicsWorld(btCollisionConfiguration* configuration,
		btBroadphaseInterface* broadphase,
		btCollisionDispatcher* dispatcher,
		btConstraintSolver* constraintSolver);
	virtual ~PhysicsWorld();

	virtual void addBody(RigidBody* body);
	virtual void addBody(RigidBody* body, CollisionFilter filter = CollisionFilter(0,-1));
	virtual void addObject(CollisionObject* object);
	virtual void addObject(CollisionObject* object, CollisionFilter filter = CollisionFilter(0,-1));

	virtual void removeBody(RigidBody* body);
	virtual void removeObject(CollisionObject* object);

	//! TODO: virtual DebugDrawer* createDebugDrawer();
	virtual void setDebugDrawer(DebugDrawer* drawer);

	virtual void castRay(Vector3d<f32> from, Vector3d<f32> to,
		RayResultCallback* callback);
#if 0
	virtual void collisionSweep(CollisionShape shape, Vector3d<f32> from,
		Vector3d<f32> to, ConvexSweepCallback* callback);
#endif

	virtual bool step();

	btScalar getDeltaTime();

	virtual PhysicsWorld::Details* getDetails() 
	{
		return &details_;
	}
private:
	DebugDrawer* debugDrawer_;

	btCollisionConfiguration* collisionConfiguration_;

	btBroadphaseInterface* broadphase_;
	btCollisionDispatcher* dispatcher_;
	btConstraintSolver*    solver_;

	btDynamicsWorld* dynamicsWorld_;

	PhysicsWorld::Details details_;

	btClock clock_;
};

} // namespace bullet
} // namespace physics
} // namespace hrengin
#endif//_hrengin_PhysicsWorld_impl_
