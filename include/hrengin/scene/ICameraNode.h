/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ICameraNode_
#define _hrengin_ICameraNode_

#include <hrengin/math/Line3d.h>

#include <hrengin/scene/ISceneNode.h>

namespace hrengin {
namespace scene {
//! Scene node which is a camera, scene is rendered from active camera's POV
class ICameraNode : public INode {
public:
	//! Virtual destructor
	virtual ~ICameraNode()
	{
	}

	//! Set target to track
	virtual void setTarget(INode* target) = 0;

	//! Reset target, camera will no longer track
	virtual void resetTarget() = 0;

	//! Set camera's field of view
	virtual void setFOV(f64 fov) = 0;

	//! Set camera's near plane distance
	virtual void setNearPlane(f64 dist) = 0;

	//! Set camera's far plane distance
	virtual void setFarPlane(f64 dist) = 0;

	//! Get world-space ray from screen-space coordinates
	virtual Line3d<f32> getRayFromScreen(i32 x, i32 y) = 0;
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_ICameraNode_