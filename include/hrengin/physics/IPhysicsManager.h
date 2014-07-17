#ifndef __HRENGIN_PHYSICS_IPhysicsManager_H__
#define __HRENGIN_PHYSICS_IPhysicsManager_H__

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/hrenginapi.h>

#include <hrengin/common/Vector3d.h>

#include <hrengin/physics/PhysModel.h>

namespace hrengin {
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

	//virtual IPhysicsBody* createBody(const u32 modelId)=0;
	//virtual IPhysicsBody* createBody(const char* modelName)=0;
	virtual IPhysicsPhantom* createPhantom(const u32 modelId)=0;
	//virtual IPhysicsPhantom* createPhantom(const char* modelName)=0;

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to) = 0;

	virtual bool step() = 0;
};

HRENGINPHYSICS_API IPhysicsManager& getPhysicsManager();

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_IPhysicsManager_H__