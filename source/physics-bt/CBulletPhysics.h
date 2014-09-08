/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CBulletPhysics_
#define _hrengin_CBulletPhysics_

#include <map>
#include <string>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <hrengin/physics/IPhysicsManager.h>


namespace hrengin {

struct SPrimitive;
struct SMesh;

class IModel;

namespace physics {

class CPhysicsPhantom;
class CPhysicsBody;

class CBulletPhysics : public IPhysicsManager {
public:
	CBulletPhysics();
	virtual ~CBulletPhysics();

	btScalar getDeltaTime();
	
	virtual u32 loadModel(const char* modelName);
	
	virtual IPhysicsBody* createBody(const u32 modelId, Vector3d<f32> pos, u16 group = 0, u16 filters = 0);
	virtual IPhysicsBody* createBody(const char* modelName, Vector3d<f32> pos, u16 group = 0, u16 filters = 0);

	virtual IPhysicsPhantom* createPhantom(const u32 modelId, u16 group = 0, u16 filters = 0);
	virtual IPhysicsPhantom* createPhantom(const char* modelName, u16 group = 0, u16 filters = 0);

	virtual IPhysicsObject* castRay(Vector3d<f32> from, Vector3d<f32> to, u16 filters = 0);

	virtual IDebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer);

	virtual void debugDraw();

	virtual bool step();

private:
	virtual u32 addShape(IModel* model);
	virtual btCollisionShape* createPrimitiveShape(SPrimitive shape);
	//virtual btCollisionShape* createMeshShape(SMesh shape);

	btClock	m_clock;

	IModelLoader* modelLoader_;
	IDebugDrawer* debugDrawer_;
	std::map<std::string,u32> models_;
	btAlignedObjectArray<btCollisionShape*>	collisionShapes_;

	btDefaultCollisionConfiguration*	m_collisionConfiguration;

	btBroadphaseInterface*	m_broadphase;
	btCollisionDispatcher*	m_dispatcher;
	btConstraintSolver*	m_solver;

	btDynamicsWorld*	m_dynamicsWorld;
};

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_CBulletPhysics_H__