/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CustomRayCallback_
#define _aw_CustomRayCallback_
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/physics/RayResultCallback.h>

#include "hrToBullet.h"

namespace aw {
namespace physics {

struct CustomClosestHitCallback
	: public btCollisionWorld::ClosestRayResultCallback {

	CustomClosestHitCallback(
		btVector3 const& rayFromWorld,
		btVector3 const& rayToWorld,
		physics::RayResultCallback* hrCallback)
	: btCollisionWorld::ClosestRayResultCallback(rayFromWorld, rayToWorld),
		customCallback_(hrCallback)
	{
		m_collisionFilterGroup = customCallback_->collFilter.group;
		m_collisionFilterMask = customCallback_->collFilter.mask;
	}

	physics::RayResultCallback* customCallback_;

	//used to calculate hitPointWorld from hitFraction
	// btVector3	m_rayFromWorld;
	// btVector3	m_rayToWorld;

	// btVector3	m_hitNormalWorld;
	// btVector3	m_hitPointWorld;

	virtual bool needsCollision(btBroadphaseProxy* proxy0) const
	{
		void* userPointer = ((btCollisionObject*)proxy0->m_clientObject)->getUserPointer();
		CollisionFilter filter(proxy0->m_collisionFilterGroup,
			proxy0->m_collisionFilterMask);
		BroadphaseProxy proxy(userPointer, filter);

		return customCallback_->needsCollision(&proxy);
	}

	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
	{
		//caller already does the filter on the m_closestHitFraction
		btAssert(rayResult.m_hitFraction <= m_closestHitFraction);

		m_closestHitFraction = rayResult.m_hitFraction;
		m_collisionObject = rayResult.m_collisionObject;
		if (normalInWorldSpace) {
			m_hitNormalWorld = rayResult.m_hitNormalLocal;
		} else {
			m_hitNormalWorld = m_collisionObject->getWorldTransform().getBasis() * rayResult.m_hitNormalLocal;
		}
		m_hitPointWorld.setInterpolate3(m_rayFromWorld,m_rayToWorld,rayResult.m_hitFraction);

		RaytestResult result(
			(CollisionObject*)m_collisionObject->getUserPointer(),
			m_closestHitFraction, 
			toHrengin(m_hitPointWorld), toHrengin(m_hitNormalWorld));

		customCallback_->addResult(result);

		return rayResult.m_hitFraction;
	}
};

#if 0
template <typename T, bool isSingleHit = T::singleHit>
struct RayCallback;

template <typename T, bool true>
struct RayCallback {
	RayCallback(btVector3 from, brVector3 to, T callback)
		: value(from, to, callback)
	CustomClosestHitCallback value;
};

template <typename T, bool false>
struct RayCallback {
	RayCallback(btVector3 from, brVector3 to, T callback)
		: value(from, to, callback)
	CustomAllHitCallback value;
};
#endif

} // namespace physics
} // namespace aw

#endif //_aw_CustomRayCallback_
