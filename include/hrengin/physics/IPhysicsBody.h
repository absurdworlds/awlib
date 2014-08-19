#ifndef __HRENGIN_PHYSICS_IPhysicsBody_H__
#define __HRENGIN_PHYSICS_IPhysicsBody_H__

#include <hrengin/physics/IPhysicsObject.h>

namespace hrengin {
namespace physics {

class IPhysicsBody : public IPhysicsObject
{
public:
	virtual Vector3d getPosition() = 0;
	virtual Vector3d getRotation() = 0;
protected:
};

}
} // namespace hrengin

#endif//__HRENGIN_PHYSICS_IPhysicsBody_H__ 