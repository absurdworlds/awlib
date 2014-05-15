
#ifndef __HG_CPhysicsPhantom__
#define __HG_CPhysicsPhantom__

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <Base/hrTypes.h>
#include <Physics/IPhysicsPhantom.h>

namespace hrengin
{
namespace physics
{

class CPhysicsPhantom : public IPhysicsPhantom
{
	public:
		CPhysicsPhantom(btCollisionObject* pCollObject);
		CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach);

		virtual void AttachToEntity(IBaseEntity* pAttach) {};

		virtual void SetPosition(Vectorf3d pos) {};
		virtual void SetRotation(Vectorf3d rot) {};

	protected:
		IBaseEntity* AttachedTo;
		btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//__HG_CPhysicsPhantom__