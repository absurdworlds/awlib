/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <irrlicht/irrlicht.h>

#include <aw/math/Vector3d.h>
#include <aw/math/Line3d.h>

#include <aw/graphics/CameraController.h>

#include "CVideoManager.h"

#include "CameraNode.h"
#include "CIrrDummyNode.h"

#include "hrToIrr.h"

namespace aw {
namespace scene {

CameraNode_::CameraNode_(SceneManager* sceneManager,
	irr::scene::ICameraSceneNode* camNode,
	irr::scene::ISceneManager* irrScMgr,
	irr::IrrlichtDevice* device)
	: camera_(camNode), scmgr_(irrScMgr), device_(device)
{
	dummy_ = new CIrrDummyNode(this, camera_->getSceneManager());
	dummy_->addChild(camera_);
}

CameraNode_::~CameraNode_()
{
	camera_->remove();
	dummy_->remove();
}

Line3d<f32> CameraNode_::getRayFromScreen(i32 x, i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), camera_);

	return toHrengin(line);
}

void CameraNode_::setTarget(Node* target)
{
}
void CameraNode_::resetTarget()
{
}

void CameraNode_::setFOV(f64 fov)
{
	camera_->setFOV(fov);
}
void CameraNode_::setNearPlane(f64 dist)
{
	camera_->setNearValue(dist);
}
void CameraNode_::setFarPlane(f64 dist)
{
	camera_->setFarValue(dist);
}

} // namespace scene
} // namespace aw
