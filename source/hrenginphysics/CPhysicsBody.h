#ifndef _hrengin_CPhysicsBody_
#define _hrengin_CPhysicsBody_

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/entities/IBaseEntity.h>
#include <hrengin/physics/IPhysicsBody.h>
//#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
namespace physics {

class CPhysicsBody : public IPhysicsBody {
public:
	CPhysicsBody(btCollisionObject* pCollObject);
	CPhysicsBody(btCollisionObject* pCollObject, IBaseEntity* pAttach);

	virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
	virtual IBaseEntity* getEntity();;

	virtual void setPosition(Vector3d pos);
	virtual void setRotation(Vector3d rot);

	virtual Vector3d getPosition();
	virtual Vector3d getRotation();

protected:
	IBaseEntity* AttachedTo;
	btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//_hrengin_CPhysicsBody_