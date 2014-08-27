#ifndef _hrengin_IPhysicsBody_
#define _hrengin_IPhysicsBody_

#include <hrengin/physics/IPhysicsObject.h>

namespace hrengin {
namespace physics {

class IPhysicsBody : public IPhysicsObject {
public:
	virtual Vector3d getPosition() = 0;
	virtual Vector3d getRotation() = 0;

	/* move body to a position */
	virtual void move(Vector3d pos) = 0;
protected:
};

}
} // namespace hrengin

#endif//_hrengin_IPhysicsBody_ 