/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CPhysicsWorld_
#define _hrengin_CPhysicsWorld_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/physics/IDebugDrawer.h>
#include <hrengin/physics/IPhysicsWorld.h>

namespace hrengin {
namespace physics {

class CPhysicsWorld : public IPhysicsWorld {
public:
	CPhysicsWorld(btCollisionConfiguration* configuration,
		btBroadphaseInterface* broadphase,
		btCollisionDispatcher* dispatcher,
		btConstraintSolver* constraintSolver);
	virtual ~CPhysicsWorld();

	virtual void addBody(IRigidBody* body);
	virtual void addBody(IRigidBody* body, CollisionFilter filter = CollisionFilter(0,-1));
	virtual void addObject(ICollisionObject* object);
	virtual void addObject(ICollisionObject* object, CollisionFilter filter = CollisionFilter(0,-1));
	
	virtual void removeBody(IRigidBody* body);
	virtual void removeObject(ICollisionObject* object);

	virtual void setDebugDrawer(IDebugDrawer* drawer);

	virtual ICollisionObject* castRay(Vector3d<f32> from, Vector3d<f32> to, u16 filters = 0);

	/* temporary, until VertexBuffer class is complete */
	virtual void debugDraw();

	virtual bool step();

	btScalar getDeltaTime();
private:
	IDebugDrawer* debugDrawer_;

	btCollisionConfiguration* collisionConfiguration_;

	btBroadphaseInterface*	broadphase_;
	btCollisionDispatcher*	dispatcher_;
	btConstraintSolver*	solver_;

	btDynamicsWorld*	dynamicsWorld_;

	btClock clock_;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_CPhysicsWorld_
