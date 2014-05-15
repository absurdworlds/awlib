
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

}



} // namespace physics
} // namespace hrengin