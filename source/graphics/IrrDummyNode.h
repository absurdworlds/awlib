/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_IrrDummyNode_
#define _aw_IrrDummyNode_
#include <irrlicht/ISceneNode.h>
#include <irrlicht/ISceneManager.h>

#include <aw/scene/SceneNode.h>

#include "hrToIrr.h"

namespace aw {
namespace scene {

class IrrDummyNode : public irr::scene::ISceneNode {
public:
	IrrDummyNode (aw::scene::INode* node,
		irr::scene::ISceneManager* mgr)
		: irr::scene::ISceneNode(mgr->getRootSceneNode(), mgr),
		  node_(node)
	{

	}

	virtual void setParent (SceneNode* newParent)
	{
		// do not change parent, since parent system is a part of
		// aw's own scene graph system
	}

	virtual void render ()
	{
	}

	//! returns the axis aligned bounding box of this node
	irr::core::aabbox3d<irr::f32>& getBoundingBox () const
	{
		static irr::core::aabbox3d<irr::f32> aabb;
		return aabb;
	}

	irr::core::matrix4 const& getAbsoluteTransformation () const
	{
		return AbsoluteTransformation;
	}

	virtual void updateAbsolutePosition ()
	{
		AbsoluteTransformation = toIrr(node_->calculateAbsoluteTransform());
	}
private:
	aw::scene::Node* node_;
};

} // namespace scene
} // namespace aw
#endif//_aw_IrrDummyNode_
