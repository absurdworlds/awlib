/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CBulletPhysics_
#define _hrengin_CBulletPhysics_

#include <map>
#include <string>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <hrengin/physics/IPhysicsManager.h>

namespace hrengin {
struct Primitive;
struct SMesh;

class IModel;

namespace physics {
class CCollisionPhantom;
class CRigidBody;

class CBulletPhysics : public IPhysicsManager {
public:
	CBulletPhysics();
	virtual ~CBulletPhysics();
	
	virtual u32 loadModel(const char* modelName);
	
	virtual IRigidBody* createBody(const u32 modelId, IRigidBody::RigidBodyConstructionInfo cInfo);
	virtual IRigidBody* createBody(const char* modelName, IRigidBody::RigidBodyConstructionInfo cInfo);

	virtual ICollisionPhantom* createPhantom(const u32 modelId);
	virtual ICollisionPhantom* createPhantom(const char* modelName);

	virtual IPhysicsWorld* createPhysicsWorld();

	virtual IDebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer);

private:
	virtual u32 addShape(IModel* model);
	virtual btCollisionShape* createPrimitiveShape(Primitive shape);
	//virtual btCollisionShape* createMeshShape(SMesh shape);

	IModelLoader* modelLoader_;

	std::map<std::string,u32> models_;
	btAlignedObjectArray<btCollisionShape*>	collisionShapes_;
};

} // namespace physics
} // namespace hrengin
#endif//__HRENGIN_PHYSICS_CBulletPhysics_H__
