
#include "CVisNode.h"
#include "../../Common/CInternalsManager.h"

#include <algorithm>

namespace hrengin
{
namespace graphics
{
	
//! constructor
//!
CVisNode::CVisNode()
	: lastFreeSlot(0)
{

}

//! constructor
//! Attaches node to entity
CVisNode::CVisNode(IBaseEntity* attach)
	: attachedTo(attach), lastFreeSlot(0)
{
	
}

void CVisNode::AttachToEntity(IBaseEntity* attach)
{

}

void CVisNode::SetPosition(Vectorf3d pos)
{
	meshSlots[lastFreeSlot-1]->setPosition(irr::core::vector3df(pos.Y,pos.Z,pos.X));
}

void CVisNode::SetRotation(Vectorf3d rot)
{	
	meshSlots[lastFreeSlot-1]->setRotation(irr::core::vector3df(rot.X,rot.Y,rot.Z));
}

void CVisNode::SetScale(Vectorf3d scale)
{

}

i8 CVisNode::AddMesh(char * meshname)
{
	if(lastFreeSlot < maxFreeSlot)
	{
		irr::scene::IAnimatedMesh* mesh = __HRIM.videomgr->LoadMesh(meshname);
		meshSlots[lastFreeSlot] = __HRIM.videomgr->GetSceneMgr()->addAnimatedMeshSceneNode(mesh);
		lastFreeSlot++;
		return lastFreeSlot-1;
	}
	else
	{
		return -1;
	}
}

void CVisNode::RemoveMesh(i8 meshslot)
{
	if(meshslot < maxFreeSlot)
	{
		if(meshSlots[meshslot])
		{
			meshSlots[meshslot] = 0;
			if(lastFreeSlot-1 != 0)
			{
				std::swap(meshSlots[meshslot], meshSlots[lastFreeSlot-1]);
				lastFreeSlot = meshslot;
			}
		}
	}
}

void CVisNode::ReplaceMesh(i8 meshslot, char * meshname)
{
	if(meshslot < maxFreeSlot)
	{
		if(meshSlots[meshslot])
		{
			irr::scene::IAnimatedMesh* mesh = __HRIM.videomgr->LoadMesh(meshname);
			meshSlots[meshslot] = __HRIM.videomgr->GetSceneMgr()->addAnimatedMeshSceneNode(mesh);
		}
	}
}

	
} // namespace graphics
} // namespace hrengin