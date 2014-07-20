#ifndef __HRENGIN_PHYSICS_CPhysicsPhantom_H__
#define __HRENGIN_PHYSICS_CPhysicsPhantom_H__

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/entities/IBaseEntity.h>
#include <hrengin/physics/IPhysicsPhantom.h>
//#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
namespace physics {

class CPhysicsPhantom : public IPhysicsPhantom
{
public:
	CPhysicsPhantom(btCollisionObject* pCollObject);
	CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach);

	virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
	virtual IBaseEntity* getEntity();;

	virtual void setPosition(Vector3d pos);
	virtual void setRotation(Vector3d rot);

protected:
	IBaseEntity* AttachedTo;
	btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_CPhysicsPhantom_H__