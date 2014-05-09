
#include "hrcVisNode.h"
#include "../../Internal/hrcInternalsManager.h"

#include <algorithm>

namespace hrengin
{
namespace graphics
{
	
//! constructor
//!
hrcVisNode::hrcVisNode()
	: lastFreeSlot(0)
{

}

//! constructor
//! Attaches node to entity
hrcVisNode::hrcVisNode(hriBaseEntity* attach)
	: attachedTo(attach), lastFreeSlot(0)
{
	
}

void hrcVisNode::AttachToEntity(hriBaseEntity* attach)
{

}

void hrcVisNode::SetPosition(Vectorf3d pos)
{

}
void hrcVisNode::SetRotation(Vectorf3d rot)
{

}
void hrcVisNode::SetScale(Vectorf3d scale)
{

}

i8 hrcVisNode::AddMesh(char * meshname)
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
			irr::scene::IAnimatedMesh* mesh = __HRIM.videomgr->LoadMesh(meshname);
			meshSlots[meshslot] = __HRIM.videomgr->GetSceneMgr()->addAnimatedMeshSceneNode(mesh);
		}
	}
}

	
} // namespace graphics
} // namespace hrengin