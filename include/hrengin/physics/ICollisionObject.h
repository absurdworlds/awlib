/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsObject_
#define _hrengin_IPhysicsObject_

#include <hrengin/common/Vector3d.h>

namespace hrengin {

class IBaseEntity;

namespace physics {

// internal implementation details
class DCollisionObject;

class ICollisionObject {
public:
	virtual ~ICollisionObject() {};

	virtual void setPosition(Vector3d<f32> pos) = 0;
	virtual void setRotation(Vector3d<f32> rot) = 0;

	virtual void setPointer(void* ptr)
	{
		pointer_ = ptr;
	}

	virtual void* getPointer()
	{
		return pointer_;
	}

	//virtual void SetScale(Vector3d<f32> scale) = 0;
	
	/**
	   get internal implementation details, intended only for internal use
	 */
	virtual DCollisionObject* getDCollisionObject() {};
protected:
	void* pointer_;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsObject_
