
#ifndef __HG_hriSceneNode__
#define __HG_hriSceneNode__

#include <Base/hrTypes.h>
#include <Base/hrVector3d.h>

namespace hrengin
{

class hriBaseEntity;

namespace graphics
{
	

class hriSceneNode
{
	public:
		virtual void AttachToEntity(hriBaseEntity* attach) = 0;

		virtual void SetPosition(Vectorf3d pos) = 0;
		virtual void SetRotation(Vectorf3d rot) = 0;
		virtual void SetScale(Vectorf3d scale) = 0;
	protected:
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriSceneNode__