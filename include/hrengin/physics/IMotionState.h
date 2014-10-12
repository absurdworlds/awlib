/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IMotionState_
#define _hrengin_IMotionState_

#include <hrengin/scene/ISceneNode.h>

namespace hrengin {
namespace physics {

//! Motion state allows to synchronize physics world with other modules
class IMotionState {
public:
	//! Synchronize world transform from user to physics
	virtual void getWorldPosition(Vector3d<f32>& worldpos) const = 0;
	virtual void getWorldOrientation(Vector3d<f32>& worldrot) const = 0;

	//! Synchronize world transform from physics to user
	virtual void setWorldPosition(Vector3d<f32> const& worldpos) = 0;
	virtual void setWorldOrientation(Vector3d<f32> const& worldrot) = 0;
};

//! This motion state is used to synchronize physics and scene graph
class CSceneMotionState : public IMotionState {
public:
	CSceneMotionState(scene::ISceneNode* node)
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
	scene::ISceneNode* node_;
};

} // namespace graphics
} // namespace hrengin

#endif //_hrengin_IMotionState_
