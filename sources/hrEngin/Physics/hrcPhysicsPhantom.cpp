
#include "hrcPhysicsPhantom.h"

namespace hrengin
{
namespace physics
{

hrcPhysicsPhantom::hrcPhysicsPhantom(btCollisionObject* pCollObject)
	: CollObject(pCollObject)
{
	CollObject->setUserPointer(this);
}

hrcPhysicsPhantom::hrcPhysicsPhantom(btCollisionObject* pCollObject, hriBaseEntity* pAttach)
	: CollObject(pCollObject), AttachedTo(pAttach)
{

}



} // namespace physics
} // namespace hrengin