/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IPhysicsManager_
#define _hrengin_IPhysicsManager_

#include <hrengin/common/types.h>
#include <hrengin/common/api.h>
#include <hrengin/common/macro.h>

#include <hrengin/common/Vector3d.h>

#include <hrengin/graphics/IRenderingDevice.h>
#include <hrengin/physics/IDebugDrawer.h>

enum collisiontypes {
	COL_NOTHING = 0,
	COL_GROUND = BIT(0),
	COL_UNIT = BIT(1),
	COL_DEBRIS = BIT(2)
};

namespace hrengin {

class IModelLoader;

namespace physics {

class ICollisionObject;
class ICollisionPhantom;
class IRigidBody;

class IPhysicsManager {
public:
	virtual ~IPhysicsManager() {};
	
	virtual u32 loadModel(const char* modelName) = 0;

	virtual IRigidBody* createBody(const u32 modelId, Vector3d<f32> pos, u16 group = 0, u16 filters = 0) = 0;
	virtual IRigidBody* createBody(const char* modelName, Vector3d<f32> pos, u16 group = 0, u16 filters = 0) = 0;
	virtual ICollisionPhantom* createPhantom(const u32 modelId, u16 group = 0, u16 filters = 0) = 0;
	virtual ICollisionPhantom* createPhantom(const char* modelName, u16 group = 0, u16 filters = 0) = 0;

	virtual ICollisionObject* castRay(Vector3d<f32> from, Vector3d<f32> to, u16 filters = 0) = 0;

	virtual IDebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer) = 0;

	/* temporary, until VertexBuffer class is complete */
	virtual void debugDraw() = 0;

	virtual bool step() = 0;
};

HRENGINPHYSICS_API IPhysicsManager* createPhysicsManager();

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsManager_
