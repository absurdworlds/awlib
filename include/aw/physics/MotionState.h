/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_MotionState_
#define _aw_MotionState_

#include <aw/scene/SceneNode.h>

namespace aw {
namespace physics {
/*!
 * Motion state allows to synchronize physics world with other modules
 */
class MotionState {
public:
	//! Synchronize world transform from user to physics
	virtual void getWorldPosition(Vector3d<f32>& worldpos) const = 0;
	virtual void getWorldOrientation(Vector3d<f32>& worldrot) const = 0;

	//! Synchronize world transform from physics to user
	virtual void setWorldPosition(Vector3d<f32> const& worldpos) = 0;
	virtual void setWorldOrientation(Vector3d<f32> const& worldrot) = 0;
};

/*!
 * This type of motion state is used to synchronize
 * physics world and scene graph
 */
class CSceneMotionState : public MotionState {
public:
	CSceneMotionState(scene::Node* node)
		: node_(node)
	{
	}

	//! Synchronize world transform from user to physics
	virtual void getWorldPosition(Vector3d<f32>& worldpos) const
	{
		worldpos = node_->getPosition();
	}
	virtual void getWorldOrientation(Vector3d<f32>& worldrot) const
	{
		worldrot = node_->getRotation();
	}

	//! Synchronize world transform from physics to user
	virtual void setWorldPosition(Vector3d<f32> const& worldpos)
	{
		node_->setPosition(worldpos);
	}
	virtual void setWorldOrientation(Vector3d<f32> const& worldrot)
	{
		node_->setRotation(worldrot);
	}
private:
	scene::Node* node_;
};

} // namespace graphics
} // namespace aw
#endif //_aw_MotionState_
