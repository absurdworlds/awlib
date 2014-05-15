#ifndef __H_INCLUDED__HRENGIN_ICameraNode
#define __H_INCLUDED__HRENGIN_ICameraNode

#include <Graphics/Base/ISceneNode.h>

namespace hrengin
{
namespace graphics
{



class ICameraNode : public ISceneNode
{
	public:
		virtual void AttachToEntity(IBaseEntity* attach) = 0;

		virtual void SetTargetPosition(Vectorf3d pos) = 0;
		virtual void SetCameraPosition(Vectorf3d pos) = 0;

		virtual void BindTargetToCamera(bool bind) = 0;

		virtual void SetCameraFOV(f64 fov) = 0;
		virtual void SetNearPlane(f64 dist) = 0;
		virtual void SetFarPlane(f64 dist) = 0;

		virtual void SetDistance(f64 dist) = 0;

		enum CAM_Behavior
		{
			CAM_NONE = 0,
			CAM_STRATEGIC,
			CAM_FIRSTPERON,
			CAM_THIRDPERSON,
			CAM_MODELVIEWER,
			CAM_STATIC
		};

		virtual void SetBehavior(CAM_Behavior beh) = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_ICameraNode