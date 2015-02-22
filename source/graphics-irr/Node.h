/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SceneNode_
#define _hrengin_SceneNode_

#include <hrengin/scene/SceneNode.h>

namespace hrengin {
namespace scene {
//! A node in the scene graph
class Node : public Node {
public:
	virtual ~Node()
	{
	}

	//! Set node's position via vector
	virtual void setPosition(Vector3d<f32> pos)
	{
	
	}
	
	//! Set node's position via coordinates
	virtual void setPosition(f32 const X, f32 const Y, f32 const Z)
	{
	
	}

	// TODO: rename to 'setOrientation'
	//! Set node's orientation via euler angles
	virtual void setRotation(Vector3d<f32> euler)
	{
	
	}
	
	//! Set node's orientation via quaternion
	virtual void setOrientation(Quaternion<f32> const& quat)
	{
	
	}

	//! Set node's relative scale
	virtual void setScale(Vector3d<f32> scale)
	{
	
	}
	
	//! Get node's position
	virtual Vector3d<f32> getPosition()
	{
	
	}

	//! Get node's orientation
	virtual Vector3d<f32> getRotation()
	{
	
	}
};

} // namespace graphics
} // namespace hrengin
#endif //_hrengin_Node_
