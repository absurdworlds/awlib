#ifndef __H_INCLUDED__HRENGIN_ISceneNode
#define __H_INCLUDED__HRENGIN_ISceneNode

#include <Base/hrTypes.h>
#include <Base/Vector3d.h>

namespace hrengin
{

class IBaseEntity;

namespace graphics
{
	

class ISceneNode
{
	public:
		virtual void AttachToEntity(IBaseEntity* attach) = 0;

		virtual void SetPosition(Vectorf3d pos) = 0;
		virtual void SetRotation(Vectorf3d rot) = 0;
		virtual void SetScale(Vectorf3d scale) = 0;
	protected:
		Vector3d mPosition;
		Vector3d mRotation;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_ISceneNode__