/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include <Irrlicht/IAnimatedMeshSceneNode.h>

#include "CSceneManager.h"
#include "CVisNode.h"
#include "CIrrDummyNode.h"

#include "hrToIrr.h"

namespace hrengin {
namespace scene {

CVisNode::CVisNode(CSceneManager* sceneManager, 
	irr::scene::IAnimatedMeshSceneNode* meshNode)
	: meshNode_(meshNode)
{
	dummy_ = new CIrrDummyNode(this, meshNode->getSceneManager());
	dummy_->addChild(meshNode);
}

CVisNode::~CVisNode()
{
	meshNode_->remove();
	dummy_->remove();
	//TODO:
	//meshNode_->delete();
}

//void CVisNode::setMesh(IMesh* mesh)
void CVisNode::setMesh(char const* mesh)
{
	irr::scene::IAnimatedMesh* irrMesh = sceneManager_->convertMesh(mesh);
	meshNode_->setMesh(irrMesh);
}

} // namespace graphics
} // namespace hrengin
