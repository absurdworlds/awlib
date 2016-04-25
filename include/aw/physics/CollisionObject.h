/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_PhysicsObject_
#define _aw_PhysicsObject_
#include <aw/utility/hidden_impl.h>

#include <aw/math/Vector3d.h>

#include <aw/physics/CollisionFilter.h>

namespace aw {
namespace physics {
//! Represents a static collision object
class CollisionObject {
public:
	virtual ~CollisionObject() = default;

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
} // namespace aw
#endif//_aw_PhysicsObject_
