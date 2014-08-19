#ifndef __HRENGIN_PHYSICS_IPhysicsObject_H__
#define __HRENGIN_PHYSICS_IPhysicsObject_H__

#include <hrengin/common/Vector3d.h>

namespace hrengin {

class IBaseEntity;

namespace physics {

class ICollisionShape;

class IPhysicsObject
{
public:
	virtual void attachToEntity(IBaseEntity* attach) = 0;
	virtual IBaseEntity* getEntity() = 0;

	virtual void setPosition(Vector3d pos) = 0;
	virtual void setRotation(Vector3d rot) = 0;
	//virtual void SetScale(Vectorf3d scale) = 0;
protected:
};

} // end namespace physics
} // end namespace hrengin

#endif//__HRENGIN_PHYSICS_IPhysicsObject_H__