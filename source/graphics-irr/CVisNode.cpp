#include <algorithm>

#include <Irrlicht/IAnimatedMeshSceneNode.h>

#include <hrengin/game/IBaseEntity.h>

#include "CSceneManager.h"

#include "CVisNode.h"



namespace hrengin {
namespace graphics {


CVisNode::CVisNode(CSceneManager* sceneManager, 
	irr::scene::IAnimatedMeshSceneNode* meshNode)
{

}

void CVisNode::setParentEntity(IBaseEntity* parent)
{
	parent_ = parent;
}

void CVisNode::setPosition(Vector3d pos)
{
	meshNode_->setPosition(irr::core::vector3df(pos.X,pos.Y,pos.Z));
}

void CVisNode::setRotation(Vector3d rot)
{
	meshNode_->setRotation(irr::core::vector3df(rot.X,rot.Y,rot.Z));
}

void CVisNode::setMesh(IMesh* mesh)
{
	irr::scene::IAnimatedMesh* irrMesh = sceneManager_->convertMesh(mesh);
	meshNode_->setMesh(irrMesh);
}

	
} // namespace graphics
} // namespace hrengin