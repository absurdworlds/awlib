
#include "hrcVisNode.h"

#include <algorithm>

namespace hrengin
{
namespace graphics
{
	
//! default constructor
//!
hrcVisNode::hrcVisNode(hriVideoManager* Vmgr)
	: videomgr(Vmgr), lastFreeSlot(0)
{

}

//! default constructor
//! Attaches node to entity
hrcVisNode::hrcVisNode(hriVideoManager* Vmgr, hriBaseEntity* attach)
	: videomgr(Vmgr), attachedTo(attach), lastFreeSlot(0)
{
	
}

void hrcVisNode::AttachToEntity(hriBaseEntity* attach)
{

}

i8 hrcVisNode::AddMesh(char * meshname)
{
	if(lastFreeSlot < maxFreeSlot)
	{
		irr::scene::IAnimatedMesh* mesh = videomgr->LoadMesh(meshname);
		meshSlots[lastFreeSlot] = videomgr->GetSceneMgr()->addAnimatedMeshSceneNode(mesh);
		lastFreeSlot++;
		return lastFreeSlot-1;
	}
	else
	{
		return -1;
	}
}

void hrcVisNode::RemoveMesh(i8 meshslot)
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

void hrcVisNode::ReplaceMesh(i8 meshslot, char * meshname)
{
	if(meshslot < maxFreeSlot)
	{
		if(meshSlots[meshslot])
		{
			irr::scene::IAnimatedMesh* mesh = videomgr->LoadMesh(meshname);
			meshSlots[meshslot] = videomgr->GetSceneMgr()->addAnimatedMeshSceneNode(mesh);
		}
	}
}

	
} // namespace graphics
} // namespace hrengin