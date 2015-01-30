/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsManager_
#define _hrengin_IPhysicsManager_

#include <hrengin/common/types.h>
#include <hrengin/common/macro.h>

#include <hrengin/math/Vector3d.h>

#include <hrengin/graphics/IRenderingDevice.h>

#include <hrengin/physics/physics.h>
#include <hrengin/physics/IRigidBody.h>
#include <hrengin/physics/IDebugDrawer.h>

namespace hrengin {
namespace core {
class IModelLoader;
}

namespace physics {
class IPhysicsWorld;
class ICollisionObject;
class ICollisionPhantom;

//! Used to create physical worlds and objects
class IPhysicsManager {
public:
	/*! Destructor
	   Notice: must be called only after deletion of all physics worlds
	 */
	virtual ~IPhysicsManager() {};
	
	virtual u32 loadModel(const char* modelName) = 0;

	virtual IRigidBody* createBody(const u32 modelId, IRigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual IRigidBody* createBody(const char* modelName, IRigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual ICollisionPhantom* createPhantom(const u32 modelId) = 0;
	virtual ICollisionPhantom* createPhantom(const char* modelName) = 0;

	virtual IPhysicsWorld* createPhysicsWorld() = 0;

	//TODO: move to IPhysicsWorld
	virtual IDebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer) = 0;
};

HR_PHYS_EXP IPhysicsManager* createPhysicsManager();

} // namespace physics
} // namespace hrengin
#endif//_hrengin_IPhysicsManager_
