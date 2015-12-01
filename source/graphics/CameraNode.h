/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CameraNode_
#define _aw_CameraNode_

#include <aw/graphics/VideoManager.h>

#include <aw/scene/SceneNode.h>
#include <aw/scene/CameraNode.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class CameraSceneNode;
class SceneManager;
}
}
namespace aw {
namespace scene {
class SceneManager;
class IrrDummyNode;

class CameraNode : public CameraNode {
public:
	CameraNode(SceneManager* sceneManager,
		irr::scene::ICameraSceneNode* camNode,
		irr::scene::ISceneManager* irrScMgr,
		irr::IrrlichtDevice* device);
	virtual ~CameraNode();

	virtual void setTarget(Node* target);
	virtual void resetTarget();

	virtual void setFOV(f64 fov);
	virtual void setNearPlane(f64 dist);
	virtual void setFarPlane(f64 dist);

	virtual Line3d<f32> getRayFromScreen(i32 x, i32 y);
private:
	irr::IrrlichtDevice* device_;
	irr::scene::ISceneManager* scmgr_;

	IrrDummyNode* dummy_;
	irr::scene::ICameraSceneNode* camera_;
};

} // namespace scene
} // namespace aw
#endif//_aw_CameraNode_
