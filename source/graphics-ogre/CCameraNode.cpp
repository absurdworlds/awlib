/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreViewport.h>

#include <OGRE/OgreRay.h>

#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Line3d.h>

#include "CVideoManager.h"

#include "CCameraNode.h"

namespace hrengin {
namespace graphics {

CCameraNode::CCameraNode(CSceneManager* sceneManager,
	Ogre::Camera* camNode)
	: controlBehavior(CAM_NONE), node_(camNode)//, scmgr_(irrScMgr), device_(device)
{

}

void CCameraNode::setParentEntity(IBaseEntity* parent)
{

}

hrengin::base::line3df CCameraNode::castRayFromScreen(hrengin::i32 x, hrengin::i32 y)
{
	f32 vx = f32(x) / f32(node_->getViewport()->getActualWidth());
	f32 vy = f32(y) / f32(node_->getViewport()->getActualHeight());
	Ogre::Ray ray = node_->getCameraToViewportRay(vx, vy);

	return toHrengin(ray);
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

}

} // namespace graphics
} // namespace hrengin
