/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/math/math.h>

#include "hrToBullet.h"
#include "RigidBody.h"
#include "CustomMotionState.h"

namespace hrengin {
namespace physics {
namespace bullet {

RigidBody::RigidBody(btRigidBody* body)
	: details_(body)
{
	details_.obj->setUserPointer(this);
}

void RigidBody::setMotionState(MotionState* motionState)
{
	btRigidBody* const body = (btRigidBody *)(details_.obj);

	btMotionState* ms = body->getMotionState();

	btTransform worldTrans;
	ms->getWorldTransform(worldTrans);

	delete ms;

	ms = new CustomMotionState(motionState, worldTrans);

	body->setMotionState(ms);
}

void RigidBody::setPosition(Vector3d<f32> pos)
{
	btTransform transform = details_.obj->getWorldTransform();
	transform.setOrigin(toBullet(pos));
	details_.obj->setWorldTransform(transform);
};

void RigidBody::setRotation(Vector3d<f32> rot)
{
	btTransform transform = details_.obj->getWorldTransform();
	rot *= math::RadiansInDegree;
	transform.setRotation(btQuaternion(rot[1], rot[0], rot[2]));
	details_.obj->setWorldTransform(transform);
};

Vector3d<f32> RigidBody::getPosition() const
{
	btVector3 pos = details_.obj->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> RigidBody::getRotation() const
{
	btQuaternion rot = details_.obj->getWorldTransform().getRotation();

	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

} // namespace bullet
} // namespace physics
} // namespace hrengin
