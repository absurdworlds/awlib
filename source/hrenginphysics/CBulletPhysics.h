#ifndef __HRENGIN_PHYSICS_CBulletPhysics_H__
#define __HRENGIN_PHYSICS_CBulletPhysics_H__

#include <map>
#include <string>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/core/IModelLoader.h>
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
	
	virtual u32 loadModel(const char* modelName);

	virtual IPhysicsBody* createBody(const u32 modelId);
	virtual IPhysicsBody* createBody(const char* modelName);
	virtual IPhysicsPhantom* createPhantom(const u32 modelId);
	virtual IPhysicsPhantom* createPhantom(const char* modelName);

	virtual u32 addShape(const char * modelname) {return 0;};
	virtual u32 makeShape(PhysShape type, f32 x, f32 y=1., f32 z=1.);

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to);

	virtual bool step();

private:
	btClock	m_clock;

	IModelLoader* modelLoader_;
	std::map<std::string,u32> models_;
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