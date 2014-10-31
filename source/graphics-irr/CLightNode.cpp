/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <hrengin/graphics/IVideoManager.h>

#include "CVideoManager.h"

#include "CLightNode.h"
#include "CIrrDummyNode.h"

namespace hrengin {
namespace scene {

CLightNode::CLightNode (CSceneManager* sceneManager,
	irr::scene::ILightSceneNode* lightNode)
	: node_(lightNode)
{
	dummy_ = new CIrrDummyNode(this, node_->getSceneManager());
	dummy_->addChild(node_);
}

CLightNode::~CLightNode()
{
	node_->remove();
	dummy_->remove();
}

} // namespace graphics
} // namespace hrengin
