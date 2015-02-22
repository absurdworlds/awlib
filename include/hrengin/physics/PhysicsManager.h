/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_PhysicsManager_
#define _hrengin_PhysicsManager_

#include <hrengin/common/types.h>
#include <hrengin/common/macro.h>

#include <hrengin/math/Vector3d.h>

#include <hrengin/graphics/RenderingDevice.h>

#include <hrengin/physics/physics.h>
#include <hrengin/physics/RigidBody.h>
#include <hrengin/physics/DebugDrawer.h>

namespace hrengin {
namespace core {
class ModelLoader;
}

namespace physics {
class PhysicsWorld;
class CollisionObject;
class CollisionPhantom;

//! Used to create physical worlds and objects
class PhysicsManager {
public:
	/*! Destructor
	   Notice: must be called only after deletion of all physics worlds
	 */
	virtual ~PhysicsManager() {};

	virtual u32 loadModel(char const* modelName) = 0;

	virtual RigidBody* createBody(u const32 modelId, IRigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual RigidBody* createBody(char const* modelName, IRigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual CollisionPhantom* createPhantom(u const32 modelId) = 0;
	virtual CollisionPhantom* createPhantom(char const* modelName) = 0;

	virtual PhysicsWorld* createPhysicsWorld() = 0;

	//TODO: move to PhysicsWorld
	virtual DebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer) = 0;
};

HR_PHYS_EXP PhysicsManager* createPhysicsManager();

} // namespace physics
} // namespace hrengin
#endif//_hrengin_PhysicsManager_
