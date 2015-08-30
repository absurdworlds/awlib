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

#include "SceneManager.h"
#include "VisNode.h"
#include "IrrDummyNode.h"

#include "hrToIrr.h"

namespace awrts {
namespace scene {

VisNode::VisNode(SceneManager* sceneManager, 
	irr::scene::IAnimatedMeshSceneNode* meshNode)
	: meshNode_(meshNode)
{
	dummy_ = new IrrDummyNode(this, meshNode->getSceneManager());
	dummy_->addChild(meshNode);
}

VisNode::~VisNode()
{
	meshNode_->remove();
	dummy_->remove();
	//TODO:
	//meshNode_->delete();
}

//void VisNode::setMesh(Mesh* mesh)
void VisNode::setMesh(char const* mesh)
{
	irr::scene::IAnimatedMesh* irrMesh = sceneManager_->convertMesh(mesh);
	meshNode_->setMesh(irrMesh);
}

} // namespace graphics
} // namespace awrts
