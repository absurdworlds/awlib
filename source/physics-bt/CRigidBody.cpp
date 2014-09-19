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
	btTransform transform = details_.obj->getWorldTransform();
	transform.setOrigin(toBullet(pos));
	details_.obj->setWorldTransform(transform);
};

void CRigidBody::setRotation(Vector3d<f32> rot)
{
	btTransform transform = details_.obj->getWorldTransform();
	rot *= math::DEGTORAD64;
	transform.setRotation(btQuaternion(rot.Y, rot.X, rot.Z));
	details_.obj->setWorldTransform(transform);
};

Vector3d<f32> CRigidBody::getPosition() const
{
	btVector3 pos = details_.obj->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> CRigidBody::getRotation() const
{
	btQuaternion rot = details_.obj->getWorldTransform().getRotation();
	
	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

} // namespace physics
} // namespace hrengin
