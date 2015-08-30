/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_BroadphaseProxy_
#define _awrts_BroadphaseProxy_

#include <awrts/common/types.h>

#include <awrts/physics/CollisionFilter.h>

namespace awrts {
namespace physics {

/* This class is used to access broadphase information */
struct BroadphaseProxy {
	void* clientObject;
	CollisionFilter collFilter;

#if 0
	Vector<f32> aabbMin;
	Vector<f32> aabbMax;
#endif

	BroadphaseProxy() 
		: clientObject(0)
	{
	}

	BroadphaseProxy(void* userPointer, CollisionFilter filter)
		: clientObject(userPointer),
		collFilter(filter)
#if 0 
		aabbMin(aabbMin),
		aabbMax(aabbMax)
#endif
	{
	}
};

} // namespace physics
} // namespace awrts
#endif//_awrts_BroadphaseProxy_
