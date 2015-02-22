/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_BulletPhysics_
#define _hrengin_BulletPhysics_
#include <map>
#include <string>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <hrengin/physics/PhysicsManager.h>

namespace hrengin {
struct Primitive;
struct SMesh;

class Model;

namespace physics {
class CollisionPhantom;
class RigidBody;

class BulletPhysics : public PhysicsManager {
public:
	BulletPhysics();
	virtual ~BulletPhysics();

	virtual u32 loadModel(const char* modelName);

	virtual RigidBody* createBody(const u32 modelId, RigidBody::RigidBodyConstructionInfo cInfo);
	virtual RigidBody* createBody(const char* modelName, RigidBody::RigidBodyConstructionInfo cInfo);

	virtual CollisionPhantom* createPhantom(const u32 modelId);
	virtual CollisionPhantom* createPhantom(const char* modelName);

	virtual PhysicsWorld* createPhysicsWorld();

	virtual DebugDrawer* createDebugDrawer(graphics::RenderingDevice* renderer);

private:
	virtual u32 addShape(Model* model);
	virtual btCollisionShape* createPrimitiveShape(Primitive shape);
	//virtual btCollisionShape* createMeshShape(SMesh shape);

	core::ModelLoader* modelLoader_;

	std::map<std::string,u32> models_;
	btAlignedObjectArray<btCollisionShape*> collisionShapes_;
};

} // namespace physics
} // namespace hrengin
#endif//_hrengin_BulletPhysics__
