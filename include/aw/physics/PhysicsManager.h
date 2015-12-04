/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_PhysicsManager_
#define _aw_PhysicsManager_

#include <aw/common/types.h>
#include <aw/utility/macro.h>

#include <aw/math/Vector3d.h>

#include <aw/graphics/RenderingDevice.h>

#include <aw/physics/physics.h>
#include <aw/physics/RigidBody.h>
#include <aw/physics/DebugDrawer.h>

namespace aw {
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
	 *  \note Should be called only after deletion of all physics worlds
	 */
	virtual ~PhysicsManager() {};

	virtual u32 loadModel(char const* modelName) = 0;

	virtual RigidBody* createBody(u32 const modelId, RigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual RigidBody* createBody(char const* modelName, RigidBody::RigidBodyConstructionInfo cInfo) = 0;
	virtual CollisionPhantom* createPhantom(u32 const modelId) = 0;
	virtual CollisionPhantom* createPhantom(char const* modelName) = 0;

	virtual PhysicsWorld* createPhysicsWorld() = 0;

	//TODO: move to PhysicsWorld
	virtual DebugDrawer* createDebugDrawer(graphics::RenderingDevice* renderer) = 0;
};

AW_PHYS_EXP PhysicsManager* createPhysicsManager();

} // namespace physics
} // namespace aw
#endif//_aw_PhysicsManager_
