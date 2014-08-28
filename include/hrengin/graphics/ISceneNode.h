#ifndef __hrengin_ISceneNode__
#define __hrengin_ISceneNode__

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {

class IBaseEntity;

namespace graphics {
	

class ISceneNode
{
	public:
		virtual void AttachToEntity(IBaseEntity* attach) = 0;

		virtual void setPosition(Vector3d pos) = 0;
		virtual void setRotation(Vector3d rot) = 0;
		// not supported
		//virtual void setScale(Vectorf3d scale) = 0;
	protected:
		Vector3d mPosition;
		Vector3d mRotation;
};

	
} // namespace graphics
} // namespace hrengin

#endif //__hrengin_ISceneNode__