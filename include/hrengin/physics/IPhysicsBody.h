#ifndef _hrengin_IPhysicsBody_
#define _hrengin_IPhysicsBody_

#include <hrengin/physics/IPhysicsObject.h>

namespace hrengin {
namespace physics {

class IPhysicsBody : public IPhysicsObject {
public:
	virtual Vector3d<f32> getPosition() = 0;
	virtual Vector3d<f32> getRotation() = 0;
protected:
};

}
} // namespace hrengin

#endif//_hrengin_IPhysicsBody_ 