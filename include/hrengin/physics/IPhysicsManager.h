#ifndef __HRENGIN_PHYSICS_IPhysicsManager_H__
#define __HRENGIN_PHYSICS_IPhysicsManager_H__

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/hrenginapi.h>

#include <hrengin/common/Vector3d.h>

#include <hrengin/physics/PhysModel.h>

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0, //<Collide with nothing
    COL_GROUND = BIT(0), //<Collide with ships
    COL_UNIT = BIT(1), //<Collide with walls
    COL_DEBRIS = BIT(2) //<Collide with powerups
};

namespace hrengin {

class IModelLoader;

namespace physics {

class ICollisionShape;
class IPhysicsObject;
class IPhysicsBody; //: IPhysicsObject;
class IPhysicsPhantom; //: IPhysicsObject;

class IPhysicsManager
{
public:
	//virtual u32 makeShape(PhysShape type, f32 x, f32 y=0., f32 z=0.) = 0;
	//virtual u32 addShape(const char * modelname) = 0;
	
	virtual u32 loadModel(const char* modelName) = 0;

	virtual IPhysicsBody* createBody(const u32 modelId, Vector3d pos, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsBody* createBody(const char* modelName, Vector3d pos, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsPhantom* createPhantom(const u32 modelId, u16 group = 0, u16 filters = 0) = 0;
	virtual IPhysicsPhantom* createPhantom(const char* modelName, u16 group = 0, u16 filters = 0) = 0;

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to, u16 filters = 0) = 0;

	
	virtual void debugDraw() = 0;

	virtual bool step() = 0;
};

HRENGINPHYSICS_API IPhysicsManager& getPhysicsManager();

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_IPhysicsManager_H__