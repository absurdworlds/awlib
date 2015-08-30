/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_PhysicsObject_
#define _awrts_PhysicsObject_

#include <awrts/common/hidden_impl.h>

#include <awrts/math/Vector3d.h>

#include <awrts/physics/CollisionFilter.h>

namespace awrts {
namespace physics {

class CollisionObject {
public:
	virtual ~CollisionObject() {};

	virtual void setPosition(Vector3d<f32> pos) = 0;
	virtual void setRotation(Vector3d<f32> rot) = 0;

	virtual Vector3d<f32> getPosition() const = 0;
	virtual Vector3d<f32> getRotation() const = 0;

	virtual void setPointer(void* ptr)
	{
		pointer_ = ptr;
	}

	virtual void* getPointer() const
	{
		return pointer_;
	}

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(CollisionObject);
protected:
	void* pointer_;
};

} // namespace physics
} // namespace awrts
#endif//_awrts_PhysicsObject_
