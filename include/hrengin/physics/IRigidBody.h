/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsBody_
#define _hrengin_IPhysicsBody_

#include <hrengin/physics/ICollisionObject.h>

namespace hrengin {
namespace physics {

// internal implementation details
class DRigidBody;

class IRigidBody : public ICollisionObject {
public:
	virtual ~IRigidBody() {};

	virtual Vector3d<f32> getPosition() = 0;
	virtual Vector3d<f32> getRotation() = 0;

	/**
	   get internal implementation details, intended only for internal use
	 */
	virtual DRigidBody* getDRigidBody()
	{
		return 0;
	}
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsBody_
