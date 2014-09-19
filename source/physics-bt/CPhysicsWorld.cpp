/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include "CCollisionPhantom.h"
#include "CRigidBody.h"

#include "CPhysicsWorld.h"
#include "CustomRayCallback.h"

namespace hrengin {
namespace physics {

CPhysicsWorld::CPhysicsWorld(btCollisionConfiguration* configuration,
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

CPhysicsWorld::~CPhysicsWorld()
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

btScalar CPhysicsWorld::getDeltaTime()
{
	btScalar dt = (btScalar)clock_.getTimeMicroseconds();
	clock_.reset();
	return dt;
}


void CPhysicsWorld::addBody(IRigidBody* body)
{
	btRigidBody* rb = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->addRigidBody(rb);
	dynamicsWorld_->updateAabbs();
}

void CPhysicsWorld::addBody(IRigidBody* body, CollisionFilter filter)
{
	btRigidBody* rb = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->addRigidBody(rb, filter.group, filter.mask);
	dynamicsWorld_->updateAabbs();
}

void CPhysicsWorld::addObject(ICollisionObject* object)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->addCollisionObject(obj);
	//dynamicsWorld_->updateAabbs();
}

void CPhysicsWorld::addObject(ICollisionObject* object, CollisionFilter filter)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->addCollisionObject(obj, filter.group, filter.mask);
	//dynamicsWorld_->updateAabbs();
}

void CPhysicsWorld::removeBody(IRigidBody* body)
{
	btRigidBody* obj = static_cast<btRigidBody*>(body->getDetails()->obj);
	dynamicsWorld_->removeRigidBody(obj);
}

void CPhysicsWorld::removeObject(ICollisionObject* object)
{
	btCollisionObject* obj = object->getDetails()->obj;
	dynamicsWorld_->removeCollisionObject(obj);
}


void castRayMultipleTarget(btVector3 const& from, btVector3 const& to,
	IRayResultCallback* callback, btDynamicsWorld* dynamicsWorld)
{

}

void castRaySingleTarget(btVector3 const& from, btVector3 const& to,
	IRayResultCallback* callback, btDynamicsWorld* dynamicsWorld)
{
	CustomClosestHitCallback resultCallback(from, to, callback);

	
	dynamicsWorld->rayTest(from, to, resultCallback);
}

void CPhysicsWorld::castRay(Vector3d<f32> from, Vector3d<f32> to, IRayResultCallback* callback)
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

void CPhysicsWorld::setDebugDrawer(IDebugDrawer* drawer)
{
	drawer->setWorld(this);
	//btIDebugDraw* debugDraw = drawer->getDetails()->debugDraw;
}

bool CPhysicsWorld::step()
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


} // namespace physics
} // namespace hrengin
