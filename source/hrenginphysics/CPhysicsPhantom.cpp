#include "CPhysicsPhantom.h"

namespace hrengin
{
namespace physics
{

CPhysicsPhantom::CPhysicsPhantom(btCollisionObject* pCollObject)
	: CollObject(pCollObject)
{
	CollObject->setUserPointer(this);
}

CPhysicsPhantom::CPhysicsPhantom(btCollisionObject* pCollObject, IBaseEntity* pAttach)
	: CollObject(pCollObject), AttachedTo(pAttach)
{
	CollObject->setUserPointer(this);
}

void CPhysicsPhantom::setPosition(Vector3d pos) 
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(pos.X,pos.Y,pos.Z));
	
	CollObject->setWorldTransform(defaultTransform);
};


IBaseEntity* CPhysicsPhantom::getEntity()
{
	return AttachedTo;
}

} // namespace physics
} // namespace hrengin