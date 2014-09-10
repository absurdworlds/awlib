/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CCollisionObject_
#define _hrengin_CCollisionObject_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/physics/ICollisionObject.h>

namespace hrengin {
namespace physics {

// internal implementation details
class DCollisionObject {
public:
	DCollisionObject(btCollisionObject* Object) : obj(Object) {}
	btCollisionObject* obj;
};

} // namespace physics
} // namespace hrengin

#endif//_hrengin_CCollisionObject_
