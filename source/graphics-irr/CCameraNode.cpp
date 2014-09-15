/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Line3d.h>

#include "IrrExt/CSceneNodeAnimatorCameraRTS.h"

#include "CVideoManager.h"

#include "CCameraNode.h"

namespace hrengin {
namespace graphics {

CCameraNode::CCameraNode(CSceneManager* sceneManager,
	irr::scene::ICameraSceneNode* camNode,
	irr::scene::ISceneManager* irrScMgr,
	irr::IrrlichtDevice* device)
	: controlBehavior(CAM_NONE), node_(camNode), scmgr_(irrScMgr), device_(device)
{

}

void CCameraNode::setParentEntity(IBaseEntity* parent)
{

}

hrengin::base::line3df CCameraNode::getRayFromScreen(hrengin::i32 x, hrengin::i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), node_);
	return toHrengin(line);
}

#if 0
	core::line3d<f32> ln(0,0,0,0,0,0);

	if (!SceneManager)
		return ln;

	if (!camera)
		camera = SceneManager->getActiveCamera();

	if (!camera)
		return ln;

	const scene::SViewFrustum* f = camera->getViewFrustum();

	core::vector3df farLeftUp = f->getFarLeftUp();
	core::vector3df lefttoright = f->getFarRightUp() - farLeftUp;
	core::vector3df uptodown = f->getFarLeftDown() - farLeftUp;

	const core::rect<s32>& viewPort = Driver->getViewPort();
	core::dimension2d<u32> screenSize(viewPort.getWidth(), viewPort.getHeight());

	f32 dx = pos.X / (f32)screenSize.Width;
	f32 dy = pos.Y / (f32)screenSize.Height;

	if (camera->isOrthogonal())
		ln.start = f->cameraPosition + (lefttoright * (dx-0.5f)) + (uptodown * (dy-0.5f));
	else
		ln.start = f->cameraPosition;

	ln.end = farLeftUp + (lefttoright * dx) + (uptodown * dy);

	return ln;

Vector3d<f32> CCameraNode::__tempGetRayHitPlaneCoords(hrengin::i32 x, hrengin::i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), node_);
	irr::core::vector3df vec;
	irr::core::plane3df plane(irr::core::vector3d<f32>(0, 0, 0), irr::core::vector3d<f32>(0, 1, 0));
	plane.getIntersectionWithLine(line.start, line.getVector(), vec);
	return Vector3d<f32>(vec.X,0,vec.Z);
}
#endif

void CCameraNode::setPosition(Vector3d<f32> pos)
{

}
void CCameraNode::setRotation(Vector3d<f32> rot)
{

}

void CCameraNode::SetDistance(f64 dist)
{

}

void CCameraNode::SetTargetPosition(Vector3d<f32> pos)
{

}
void CCameraNode::SetCameraPosition(Vector3d<f32> pos)
{

}

void CCameraNode::BindTargetToCamera(bool bind)
{

}

void CCameraNode::SetCameraFOV(f64 fov)
{

}
void CCameraNode::SetNearPlane(f64 dist)
{

}
void CCameraNode::SetFarPlane(f64 dist)
{

}

void CCameraNode::SetBehavior(CAM_Behavior beh)
{
	controlBehavior = beh;
	
	/* reset camera animator */
	if(animator)
	{
		node_->removeAnimator(animator);
		//animator->drop();
		animator = 0;

	}

	switch(controlBehavior)
	{
	case CAM_STRATEGIC:
		animator = new irr::scene::CSceneNodeAnimatorCameraRTS(device_->getCursorControl(), device_->getTimer());
		node_->addAnimator(animator);
		animator->drop();
	break;
	default:
	case CAM_NONE:
		break;
	}
}


	
} // namespace graphics
} // namespace hrengin