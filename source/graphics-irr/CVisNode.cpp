/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include <Irrlicht/IAnimatedMeshSceneNode.h>

#include <hrengin/game/IBaseEntity.h>

#include "hrToIrr.h"
#include "CSceneManager.h"
#include "CVisNode.h"

namespace hrengin {
namespace graphics {

CVisNode::CVisNode(CSceneManager* sceneManager, 
	irr::scene::IAnimatedMeshSceneNode* meshNode)
	:meshNode_(meshNode)
{

}

void CVisNode::setParentEntity(IBaseEntity* parent)
{
	parent_ = parent;
}

void CVisNode::setPosition(Vector3d<f32> pos)
{
	meshNode_->setPosition(toIrr(pos));
}

void CVisNode::setRotation(Vector3d<f32> rot)
{
	meshNode_->setRotation(toIrr(rot));
}

//void CVisNode::setMesh(IMesh* mesh)
void CVisNode::setMesh(const char* mesh)
{
	irr::scene::IAnimatedMesh* irrMesh = sceneManager_->convertMesh(mesh);
	meshNode_->setMesh(irrMesh);
}

} // namespace graphics
} // namespace hrengin
