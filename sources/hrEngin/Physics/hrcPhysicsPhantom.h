
#ifndef __HG_hrcPhysicsPhantom__
#define __HG_hrcPhysicsPhantom__

#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <Base/hrTypes.h>
#include <Physics/hriPhysicsPhantom.h>

namespace hrengin
{
namespace physics
{

class hrcPhysicsPhantom : public hriPhysicsPhantom
{
	public:
		hrcPhysicsPhantom(btCollisionObject* pCollObject);
		hrcPhysicsPhantom(btCollisionObject* pCollObject, hriBaseEntity* pAttach);

		virtual void AttachToEntity(hriBaseEntity* pAttach) {};

		virtual void SetPosition(Vectorf3d pos) {};
		virtual void SetRotation(Vectorf3d rot) {};

	protected:
		hriBaseEntity* AttachedTo;
		btCollisionObject* CollObject;
};

}	
} // namespace hrengin

#endif//__HG_hrcPhysicsPhantom__