#include <hrengin/common/math.h>

#include "CPhysicsBody.h"


namespace hrengin {
namespace physics {

CPhysicsBody::CPhysicsBody(btCollisionObject* pCollObject)
	: CollObject(pCollObject)
{
	CollObject->setUserPointer(this);
}

CPhysicsBody::CPhysicsBody(btCollisionObject* pCollObject, IBaseEntity* pAttach)
	: CollObject(pCollObject), AttachedTo(pAttach)
{
	CollObject->setUserPointer(this);
}

void CPhysicsBody::setPosition(Vector3d<f32> pos) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	btVector3 origin(pos.X,pos.Y,pos.Z);
	localTransform.setOrigin(origin);
	localTransform.setRotation(CollObject->getWorldTransform().getRotation());
	
	//CollObject->setWorldTransform(localTransform);
};


void CPhysicsBody::setRotation(Vector3d<f32> rot) 
{
	btTransform localTransform;
	localTransform.setIdentity();
	localTransform.setOrigin(CollObject->getWorldTransform().getOrigin());
	localTransform.setRotation(btQuaternion(rot.Y*math::DEGTORAD64,rot.X*math::DEGTORAD64,rot.Z*math::DEGTORAD64));
	
	//CollObject->setWorldTransform(localTransform);
};


void quaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
	btScalar W = TQuat.getW();
	btScalar X = TQuat.getX();
	btScalar Y = TQuat.getY();
	btScalar Z = TQuat.getZ();
	float WSquared = W * W;
	float XSquared = X * X;
	float YSquared = Y * Y;
	float ZSquared = Z * Z;

	TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
	TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
	TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
	TEuler *= math::RADTODEG;
}

Vector3d<f32> CPhysicsBody::getPosition() 
{
	btVector3 pos = CollObject->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> CPhysicsBody::getRotation() 
{
	btQuaternion rot = CollObject->getWorldTransform().getRotation();
	
	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

IBaseEntity* CPhysicsBody::getEntity()
{
	return AttachedTo;
}

} // namespace physics
} // namespace hrengin