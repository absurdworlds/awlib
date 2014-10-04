/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IRayResultCallback_
#define _hrengin_IRayResultCallback_

#include <hrengin/physics/ICollisionObject.h>
#include <hrengin/physics/BroadphaseProxy.h>

namespace hrengin {
namespace physics {

//! Strcut for raytest result
struct RaytestResult {
	RaytestResult(const ICollisionObject* collisionObject,
		f32 hitFrac, Vector3d<f32> hitPos, Vector3d<f32> hitNorm)
	: collObject(collisionObject),
	hitFraction(hitFrac),
	hitPosition(hitPos),
	hitNormal(hitNorm)
	{
	}

	const ICollisionObject* collObject;

	f32		hitFraction;
	Vector3d<f32>	hitNormal;
	Vector3d<f32>	hitPosition;
};

//! Interface for raytest callbacks
class IRayResultCallback {
public:
	static const bool singleHit = true;

	f32 closestHitFraction;
	CollisionFilter collFilter;

	virtual bool needsCollision(BroadphaseProxy* proxy)
	{
		bool collides = (proxy->collFilter.group & collFilter.mask) != 0;
		collides = collides && (collFilter.group & proxy->collFilter.mask);
		return collides;
	}

	virtual f32 addResult(RaytestResult& result) = 0;
	virtual bool hasHit() const = 0;
#if 0
	// internal implementation details
	class Details;

	// for internal use only
	virtual IRayResultCallback::Details* getDetails() = 0;
#endif
};

//! This class is used to report single raytest result
class IClosestHitCallback : public IRayResultCallback {
public:
	static const bool singleHit = true;

	ICollisionObject const* collObject;
	Vector3d<f32> hitPoint;
	Vector3d<f32> hitNormal;
	
	IClosestHitCallback()
		: collObject(0), hitPoint(0,0,0), hitNormal(0,0,0)
	{
		
	}
	
	virtual f32 addResult(RaytestResult& result)
	{
		collObject = result.collObject;
		closestHitFraction = result.hitFraction;
		hitPoint = result.hitPosition;
		hitNormal = result.hitNormal;

		return closestHitFraction;
	}

	virtual bool hasHit() const
	{
		return (collObject != 0);
	}

};

} // namespace graphics
} // namespace hrengin

#endif //_hrengin_IRayResultCallback_
