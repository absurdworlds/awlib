/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_PhysicsManager_
#define _awrts_PhysicsManager_

#include <awrts/common/types.h>
#include <awrts/common/macro.h>

#include <awrts/math/Vector3d.h>

#include <awrts/graphics/RenderingDevice.h>

#include <awrts/physics/physics.h>
#include <awrts/physics/RigidBody.h>
#include <awrts/physics/DebugDrawer.h>

namespace awrts {
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

HR_PHYS_EXP PhysicsManager* createPhysicsManager();

} // namespace physics
} // namespace awrts
#endif//_awrts_PhysicsManager_
