
#ifndef __HG_hriCameraNode__
#define __HG_hriCameraNode__

#include <Graphics/Base/hriSceneNode.h>

namespace hrengin
{
namespace graphics
{



class hriCameraNode : public hriSceneNode
{
	public:
		virtual void AttachToEntity(hriBaseEntity* attach) = 0;

		virtual void SetTargetPosition(Vectorf3d pos) = 0;
		virtual void SetCameraPosition(Vectorf3d pos) = 0;

};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hriVisNode__