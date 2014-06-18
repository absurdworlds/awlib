#ifndef __HRENGIN_PHYSICS_CBulletPhysics_H__
#define __HRENGIN_PHYSICS_CBulletPhysics_H__

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/physics/IPhysicsManager.h>

#include "CPhysicsPhantom.h"

namespace hrengin {
namespace physics {

class CBulletPhysics : public IPhysicsManager
{
public:
	CBulletPhysics();
	~CBulletPhysics();

	btScalar getDeltaTime();

	virtual IPhysicsBody* createBody(const u32 shapeid) {return 0;};
	virtual IPhysicsPhantom* createPhantom(const u32 shapeid);

	virtual u32 addShape(const char * modelname) {return 0;};
	virtual u32 makeShape(IPhysicsManager::PhysShape type, f32 x, f32 y=1., f32 z=1.);

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to);

	virtual bool step();

private:
	btClock	m_clock;

	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btDefaultCollisionConfiguration*	m_collisionConfiguration;

	btBroadphaseInterface*	m_broadphase;
	btCollisionDispatcher*	m_dispatcher;
	btConstraintSolver*	m_solver;

	btDynamicsWorld*	m_dynamicsWorld;
};

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_CBulletPhysics_H__