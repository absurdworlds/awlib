/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <algorithm>

#include <OGRE/OgreMesh.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>

#include <hrengin/game/IBaseEntity.h>
#include <hrengin/common/math.h>

#include "CSceneManager.h"

#include "CVisNode.h"



namespace hrengin {
namespace graphics {


CVisNode::CVisNode(CSceneManager* sceneManager,
	Ogre::SceneNode* meshNode)
	: node_(meshNode)
{
}

void CVisNode::setParentEntity(IBaseEntity* parent)
{
	parent_ = parent;
}

void CVisNode::setPosition(Vector3d<f32> pos)
{
	node_->setPosition(pos.X, pos.Y, pos.Z);
}

void CVisNode::setRotation(Vector3d<f32> rot)
{
	/* todo: move to a separate function */
	f32 cosX = cos(rot.X);
	f32 cosY = cos(rot.Y);
	f32 cosZ = cos(rot.Z);
	f32 sinX = sin(rot.X);
	f32 sinY = sin(rot.Y);
	f32 sinZ = sin(rot.Z);
	f32 w = math::sqrt(1.0 + cosX * cosY + cosX * cosZ - sinX * sinY * sinZ + cosY * cosZ) / 2;
	f32 x = (cosY * sinZ + cosX * sinZ + sinX * sinY * cosZ) / (4.0 * w);
	f32 y = (sinX * cosY + sinX * cosZ + cosX * sinY * sinZ) / (4.0 * w);
	f32 z = (-sinX * sinZ + cosX * sinY * cosZ + sinY) /(4.0 * w);

	node_->setOrientation(w, x, y, z);
}

//void CVisNode::setMesh(IMesh* mesh)
void CVisNode::setMesh(const char* mesh)
{

}

} // namespace graphics
} // namespace hrengin
