/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CIrrDummyNode_
#define _hrengin_CIrrDummyNode_
#include <irrlicht/ISceneNode.h>
#include <irrlicht/ISceneManager.h>

#include <hrengin/scene/ISceneNode.h>

#include "hrToIrr.h"

namespace hrengin {
namespace scene {

class CIrrDummyNode : public irr::scene::ISceneNode {
public:
	CIrrDummyNode (hrengin::scene::INode* node,
		irr::scene::ISceneManager* mgr)
		: irr::scene::ISceneNode(mgr->getRootSceneNode(), mgr),
		  node_(node)
	{
	
	}

	virtual void setParent (ISceneNode* newParent)
	{
		// do not change parent, since parent system is a part of
		// hrengin's own scene graph system
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
		// AbsoluteTransformation = calcTransform();
		return AbsoluteTransformation;
	}

	virtual void updateAbsolutePosition ()
	{
		AbsoluteTransformation = toIrr(node_->calculateAbsoluteTransform());
	}
private:
	hrengin::scene::INode* node_;
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_CIrrDummyNode_
