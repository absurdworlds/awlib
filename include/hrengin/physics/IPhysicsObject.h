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
	
	/* move object to a position with physics simulation */
	virtual void move(Vector3d pos) = 0;
	
	/* set object position without running simulation */
	virtual void setPosition(Vector3d pos) = 0;
	virtual void setRotation(Vector3d rot) = 0;

	//virtual void SetScale(Vectorf3d scale) = 0;
protected:
};

} // end namespace physics
} // end namespace hrengin

#endif//_hrengin_IPhysicsObject_