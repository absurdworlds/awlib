/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CustomRayCallback_
#define _hrengin_CustomRayCallback_

#include <btBulletCollisionCommon.h>

#include <hrengin/physics/MotionState.h>

#include "hrToBullet.h"

namespace hrengin {
namespace physics {

struct CustomMotionState : public btMotionState {
	MotionState* motionState;
	btTransform centerOfMassOffset;
	btTransform startWorldTrans;

	CustomMotionState (MotionState* motionState,
		btTransform const& startTrans = btTransform::getIdentity(),
		btTransform const& centerOfMass = btTransform::getIdentity())
		: startWorldTrans(startTrans), centerOfMassOffset(centerOfMass),
			motionState(motionState)
	{

	}

	//! Synchronize world transform from user to physics
	virtual void getWorldTransform (btTransform& physicsTrans) const
	{
		Vector3d<f32> pos;
		Vector3d<f32> rot;
		motionState->getWorldPosition(pos);
		motionState->getWorldOrientation(rot);

		btTransform sceneTrans = btTransform::getIdentity();
		sceneTrans.setOrigin(toBullet(pos));
		sceneTrans.setRotation(btQuaternion(rot[1], rot[0], rot[2]));

		physicsTrans = centerOfMassOffset.inverse() * sceneTrans;
	}

	//! Synchronize world transform from physics to user
	virtual void setWorldTransform(btTransform const& physicsTrans)
	{
		btTransform sceneTrans = physicsTrans * centerOfMassOffset;
		btVector3 euler;
		quaternionToEuler(sceneTrans.getRotation(), euler);

		motionState->setWorldPosition(toHrengin(sceneTrans.getOrigin()));
		motionState->setWorldOrientation(toHrengin(euler));
	}
};

} // namespace physics
} // namespace hrengin

#endif //_hrengin_CustomRayCallback_
