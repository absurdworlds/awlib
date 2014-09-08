/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include "CVideoManager.h"

#include "CLightNode.h"

namespace hrengin{
namespace graphics{

CLightNode::CLightNode(CSceneManager* sceneManager,
	irr::scene::ILightSceneNode* lightNode)
	: node_(lightNode)
{

}

void CLightNode::setParentEntity(IBaseEntity* parent)
{

}

void CLightNode::setPosition(Vector3d<f32> pos)
{

}
void CLightNode::setRotation(Vector3d<f32> rot)
{

}
} // namespace graphics
} // namespace hrengin
