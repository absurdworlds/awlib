/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CollisionPhantom.h"
#include "RigidBody.h"

#include "PhysicsWorld.h"
#include "CustomRayCallback.h"

namespace hrengin {
namespace physics {
namespace bullet {

PhysicsWorld::PhysicsWorld(btCollisionConfiguration* configuration,
	btBroadphaseInterface* broadphase,
	btCollisionDispatcher* dispatcher,
	btConstraintSolver* constraintSolver)
	: collisionConfiguration_(configuration), broadphase_(broadphase),
	dispatcher_(dispatcher), solver_(constraintSolver)
{
	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, solver_, collisionConfiguration_);
	dynamicsWorld_->setGravity(btVector3(0,-10,0));
	details_.world = dynamicsWorld_;
}

PhysicsWorld::~PhysicsWorld()
{
	int i;

	for (i = dynamicsWorld_->getNumCollisionObjects() -1; i >= 0; -- i) {
		btCollisionObject* obj = dynamicsWorld_->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast( obj );
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		dynamicsWorld_->removeCollisionObject( obj );
		delete obj;
	}

	delete dynamicsWorld_;
	delete solver_;
	delete broadphase_;
	delete dispatcher_;
	delete collisionConfiguration_;
}

btScalar PhysicsWorld::getDeltaTime()
{
	btScalar dt = (btScalar)clock_.getTimeMicroseconds();
	clock_.reset();
	return dt;
}


void PhysicsWorld::addBody(RigidBody* body)
{
	btRigidBody* rb = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->addRigidBody(rb);
	dynamicsWorld_->updateAabbs();
}

void PhysicsWorld::addBody(RigidBody* body, CollisionFilter filter)
{
	btRigidBody* rb = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->addRigidBody(rb, filter.group, filter.mask);
	dynamicsWorld_->updateAabbs();
}

void PhysicsWorld::addObject(CollisionObject* object)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->addCollisionObject(obj);
	//dynamicsWorld_->updateAabbs();
}

void PhysicsWorld::addObject(CollisionObject* object, CollisionFilter filter)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->addCollisionObject(obj, filter.group, filter.mask);
	//dynamicsWorld_->updateAabbs();
}

void PhysicsWorld::removeBody(RigidBody* body)
{
	btRigidBody* obj = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->removeRigidBody(obj);
}

void PhysicsWorld::removeObject(CollisionObject* object)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->removeCollisionObject(obj);
}


void castRayMultipleTarget(btVector3 const& from, btVector3 const& to,
	RayResultCallback* callback, btDynamicsWorld* dynamicsWorld)
{

}

void castRaySingleTarget(btVector3 const& from, btVector3 const& to,
	RayResultCallback* callback, btDynamicsWorld* dynamicsWorld)
{
	CustomClosestHitCallback resultCallback(from, to, callback);


	dynamicsWorld->rayTest(from, to, resultCallback);
}

void PhysicsWorld::castRay(Vector3d<f32> from, Vector3d<f32> to, RayResultCallback* callback)
{
#if 0
	typedef void (* rayCastFunc)(btVector3, btVector3, IRayResultCallback*);
	static rayCastFunc jumpTable[2];
#endif

	switch(callback->singleHit) {
	case true:
		castRaySingleTarget(toBullet(from),toBullet(to),
			callback, dynamicsWorld_);
		break;
	case false:
		castRayMultipleTarget(toBullet(from),toBullet(to),
			callback, dynamicsWorld_);
		break;
	}
}

void PhysicsWorld::setDebugDrawer(DebugDrawer* drawer)
{
	drawer->setWorld(this);
	//btIDebugDraw* debugDraw = drawer->getDetails()->debugDraw;
}

bool PhysicsWorld::step()
{
	btScalar ms = getDeltaTime();

	if (!dynamicsWorld_) {
		return false;
	}

	static const btScalar subSteps = 1;
	static const btScalar timeStep = 1.0f / 60.0f;

	dynamicsWorld_->stepSimulation(ms / 1000000.0f, subSteps, timeStep);

	return true;
}
} // namespace bullet
} // namespace physics
} // namespace hrengin
