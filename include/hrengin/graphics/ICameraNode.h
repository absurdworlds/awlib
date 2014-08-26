#ifndef _hrengin_ICameraNode_
#define _hrengin_ICameraNode_

#include <hrengin/common/line3d.h>
#include <hrengin/graphics/ISceneNode.h>

namespace hrengin {
namespace graphics {



class ICameraNode : public ISceneNode {
public:
	virtual void AttachToEntity(IBaseEntity* attach) = 0;

	virtual void SetTargetPosition(Vector3d pos) = 0;
	virtual void SetCameraPosition(Vector3d pos) = 0;

	virtual void BindTargetToCamera(bool bind) = 0;

	virtual void SetCameraFOV(f64 fov) = 0;
	virtual void SetNearPlane(f64 dist) = 0;
	virtual void SetFarPlane(f64 dist) = 0;

	virtual void SetDistance(f64 dist) = 0;

	virtual hrengin::base::line3df castRayFromScreen(hrengin::i32 x, hrengin::i32 y) = 0;
	virtual hrengin::Vector3d __tempGetRayHitPlaneCoords(hrengin::i32 x, hrengin::i32 y) = 0;

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