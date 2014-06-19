#ifndef __HRENGIN_PHYSICS_IPhysicsManager_H__
#define __HRENGIN_PHYSICS_IPhysicsManager_H__

#include <hrengin/common/hrTypes.h>
#include <hrengin/common/hrenginapi.h>

#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace physics {

class ICollisionShape;
class IPhysicsObject;
class IPhysicsBody; //: IPhysicsObject;
class IPhysicsPhantom; //: IPhysicsObject;

class IPhysicsManager
{
public:
	enum PhysShape
	{
		PHYS_SHAPE_SPHERE,
		PHYS_SHAPE_BOX,
		PHYS_SHAPE_CAPSULE,
		PHYS_SHAPE_CYLINDER,
		PHYS_SHAPE_CONE
	};

	virtual u32 makeShape(PhysShape type, f32 x, f32 y=0., f32 z=0.) = 0;
	virtual u32 addShape(const char * modelname) = 0;

	virtual IPhysicsBody* createBody(const u32 shapeid) = 0;
	virtual IPhysicsPhantom* createPhantom(const u32 shapeid) = 0;

	virtual IPhysicsObject* castRay(Vectorf3d from, Vectorf3d to) = 0;

	virtual bool step() = 0;
};

HRENGINPHYSICS_API IPhysicsManager& getPhysicsManager();

} // namespace physics
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_IPhysicsManager_H__