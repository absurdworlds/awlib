/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ICameraNode_
#define _hrengin_ICameraNode_

#include <hrengin/common/Line3d.h>
#include <hrengin/graphics/ISceneNode.h>

namespace hrengin {
namespace graphics {

//! Scene node which is a camera, scene is rendered from active camera's POV
class ICameraNode : public ISceneNode {
public:
	//! Virtual destructor
	virtual ~ICameraNode() {};

	virtual void SetTargetPosition(Vector3d<f32> pos) = 0;
	virtual void SetCameraPosition(Vector3d<f32> pos) = 0;

	virtual void BindTargetToCamera(bool bind) = 0;

	virtual void SetCameraFOV(f64 fov) = 0;
	virtual void SetNearPlane(f64 dist) = 0;
	virtual void SetFarPlane(f64 dist) = 0;

	virtual void SetDistance(f64 dist) = 0;

	//! Get world-space ray from screen-space coordinates
	virtual Line3d<f32> getRayFromScreen(i32 x, i32 y) = 0;

	// TODO: replace this with ICameraController class
	enum CAM_Behavior {
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

#endif//_hrengin_ICameraNode_
