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

class ICollisionShape;

class IPhysicsObject {
public:
	virtual void attachToEntity(IBaseEntity* attach) = 0;
	virtual IBaseEntity* getEntity() = 0;
	
	virtual void setPosition(Vector3d<f32> pos) = 0;
	virtual void setRotation(Vector3d<f32> rot) = 0;

	//virtual void SetScale(Vector3d<f32> scale) = 0;
protected:
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsObject_
