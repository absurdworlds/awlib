/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CCameraNode_
#define _hrengin_CCameraNode_

#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/game/IBaseEntity.h>

namespace Ogre {
class Camera;
}

namespace hrengin {
namespace graphics {
class CSceneManager;

class CCameraNode : public ICameraNode {
public:
	CCameraNode(CSceneManager* sceneManager,
		Ogre::Camera* camNode);

	virtual void setParentEntity(IBaseEntity* parent);

	virtual hrengin::base::line3df getRayFromScreen(hrengin::i32 x, hrengin::i32 y);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

	virtual void SetTargetPosition(Vector3d<f32> pos);
	virtual void SetCameraPosition(Vector3d<f32> pos);

	virtual void BindTargetToCamera(bool bind);

	virtual void SetCameraFOV(f64 fov);
	virtual void SetNearPlane(f64 dist);
	virtual void SetFarPlane(f64 dist);

	virtual void SetDistance(f64 dist);

	virtual void SetBehavior(CAM_Behavior beh);
private:
	IBaseEntity* attachedTo;

	CAM_Behavior controlBehavior;

	Ogre::Camera* node_;
};

	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CCameraNode_
