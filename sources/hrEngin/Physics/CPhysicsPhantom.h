#ifndef __H_INCLUDED__HRENGIN_CPhysicsPhantom
#define __H_INCLUDED__HRENGIN_CPhysicsPhantom

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/common/hrTypes.h>
#include <hrengin/physics/IPhysicsPhantom.h>

namespace hrengin
{
namespace physics
{

class CPhysicsPhantom : public IPhysicsPhantom
{
	public:
		CPhysicsPhantom(btCollisionObject* pCollObject);
		CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach);

		virtual void attachToEntity(IBaseEntity* pAttach) {AttachedTo = pAttach;};
		virtual IBaseEntity* getEntity();;

		virtual void setPosition(Vector3d pos);
		virtual void setRotation(Vector3d rot) {};

	protected:
		IBaseEntity* AttachedTo;
		btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_CPhysicsPhantom