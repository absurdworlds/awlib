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

class ICollisionShape;
class IPhysicsObject;
class IPhysicsBody; //: IPhysicsObject;
class IPhysicsPhantom; //: IPhysicsObject;

class IPhysicsManager {
public:
	virtual ~IPhysicsManager() {};
	//virtual u32 makeShape(PhysShape type, f32 x, f32 y=0., f32 z=0.) = 0;
	//virtual u32 addShape(const char * modelname) = 0;
	
	virtual u32 loadModel(const char* modelName) = 0;

	virtual IPhysicsBody* createBody(const u32 modelId, Vector3d pos, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsBody* createBody(const char* modelName, Vector3d pos, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsPhantom* createPhantom(const u32 modelId, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsPhantom* createPhantom(const char* modelName, u16 group = 0, u16 filters = 0) = 0;

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to, u16 filters = 0) = 0;

	virtual IDebugDrawer* createDebugDrawer(graphics::IRenderingDevice* renderer) = 0;

	/* temporary, until VertexBuffer class is complete */
	virtual void debugDraw() = 0;

	virtual bool step() = 0;
};

HRENGINPHYSICS_API IPhysicsManager& getPhysicsManager();

} // namespace physics
} // namespace hrengin

#endif//_hrengin_IPhysicsManager_