/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <hrengin/common/math.h>

#include "hrToBullet.h"
#include "CRigidBody.h"

namespace hrengin {
namespace physics {

CRigidBody::CRigidBody(btRigidBody* body)
	: details_(body)
{
	details_.obj->setUserPointer(this);
}

void CRigidBody::setPosition(Vector3d<f32> pos) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	btVector3 origin(pos.X,pos.Y,pos.Z);
	localTransform.setOrigin(origin);
	localTransform.setRotation(details_.obj->getWorldTransform().getRotation());
	
	//CollObject->setWorldTransform(localTransform);
};


void CRigidBody::setRotation(Vector3d<f32> rot) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	localTransform.setOrigin(details_.obj->getWorldTransform().getOrigin());
	localTransform.setRotation(btQuaternion(rot.Y*math::DEGTORAD64,rot.X*math::DEGTORAD64,rot.Z*math::DEGTORAD64));
	
	//CollObject->setWorldTransform(localTransform);
};

Vector3d<f32> CRigidBody::getPosition() 
{
	btVector3 pos = details_.obj->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> CRigidBody::getRotation() 
{
	btQuaternion rot = details_.obj->getWorldTransform().getRotation();
	
	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

} // namespace physics
} // namespace hrengin
