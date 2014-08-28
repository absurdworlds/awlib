#ifndef _hrengin_ISceneNode_
#define _hrengin_ISceneNode_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

class IBaseEntity;

namespace graphics {
	

class ISceneNode {
public:
	virtual void AttachToEntity(IBaseEntity* attach) = 0;

	virtual void setPosition(Vector3d pos) = 0;
	virtual void setRotation(Vector3d rot) = 0;
	// not supported
	//virtual void setScale(Vectorf3d scale) = 0;
protected:
	Vector3d position_;
	Vector3d rotation_;
};

	
} // namespace graphics
} // namespace hrengin

#endif //_hrengin_ISceneNode_
