/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Line3d.h>
#include <hrengin/graphics/ICameraController.h>

#include "IrrExt/CSceneNodeAnimatorCameraRTS.h"

#include "CVideoManager.h"

#include "CCameraNode.h"

#include "hrToIrr.h"

namespace hrengin {
namespace scene {

CCameraNode::CCameraNode(CSceneManager* sceneManager,
	irr::scene::ICameraSceneNode* camNode,
	CConversionTable* convTable,
	irr::scene::ISceneManager* irrScMgr,
	irr::IrrlichtDevice* device)
	: controlBehavior(CAM_NONE), camera_(camNode),
	  scmgr_(irrScMgr), device_(device),
	  convTable_(convTable)
{

}

Line3d<f32> CCameraNode::getRayFromScreen(i32 x, i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), camera_);

	return toHrengin(line);
}

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
		camera_->removeAnimator(animator);
		//animator->drop();
		animator = 0;

	}

	switch(controlBehavior)
	{
	case CAM_STRATEGIC:
		animator = new irr::scene::CSceneNodeAnimatorCameraRTS(device_->getCursorControl(), device_->getTimer());
		camera_->addAnimator(animator);
		animator->drop();
	break;
	default:
	case CAM_NONE:
		break;
	}
}
	
} // namespace scene
} // namespace hrengin
