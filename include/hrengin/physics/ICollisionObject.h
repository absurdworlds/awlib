/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsObject_
#define _hrengin_IPhysicsObject_

#include <hrengin/common/hidden_impl.h>

#include <hrengin/math/Vector3d.h>

#include <hrengin/physics/CollisionFilter.h>

namespace hrengin {
namespace physics {

class ICollisionObject {
public:
	virtual ~ICollisionObject() {};

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
	DECLARE_HIDDEN_DETAILS(ICollisionObject);
protected:
	void* pointer_;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsObject_
