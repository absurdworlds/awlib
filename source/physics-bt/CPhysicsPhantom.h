#ifndef _hrengin_CPhysicsPhantom_
#define _hrengin_CPhysicsPhantom_

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/hrengintypes.h>
#include <hrengin/entities/IBaseEntity.h>
#include <hrengin/physics/IPhysicsPhantom.h>
//#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
namespace physics {

class CPhysicsPhantom : public IPhysicsPhantom {
public:
	CPhysicsPhantom(btCollisionObject* pCollObject);
	CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach);

	virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
	virtual IBaseEntity* getEntity();

	virtual void setPosition(Vector3d pos);
	virtual void setRotation(Vector3d rot);

protected:
	IBaseEntity* AttachedTo;
	btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//_hrengin_CPhysicsPhantom_