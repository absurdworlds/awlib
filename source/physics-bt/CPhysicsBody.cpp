/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <hrengin/common/math.h>

#include "hrToBullet.h"
#include "CPhysicsBody.h"


namespace hrengin {
namespace physics {

CPhysicsBody::CPhysicsBody(btRigidBody* body)
	: details_(body)
{
	details_.body->setUserPointer(this);
}

void CPhysicsBody::setPosition(Vector3d<f32> pos) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	btVector3 origin(pos.X,pos.Y,pos.Z);
	localTransform.setOrigin(origin);
	localTransform.setRotation(details_.body->getWorldTransform().getRotation());
	
	//CollObject->setWorldTransform(localTransform);
};


void CPhysicsBody::setRotation(Vector3d<f32> rot) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	localTransform.setOrigin(details_.body->getWorldTransform().getOrigin());
	localTransform.setRotation(btQuaternion(rot.Y*math::DEGTORAD64,rot.X*math::DEGTORAD64,rot.Z*math::DEGTORAD64));
	
	//CollObject->setWorldTransform(localTransform);
};


void  CPhysicsBody::setPointer(void* ptr)
{
	pointer_ = ptr;
}

void* CPhysicsBody::getPointer()
{
	return pointer_;
}

Vector3d<f32> CPhysicsBody::getPosition() 
{
	btVector3 pos = details_.body->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> CPhysicsBody::getRotation() 
{
	btQuaternion rot = details_.body->getWorldTransform().getRotation();
	
	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

} // namespace physics
} // namespace hrengin
