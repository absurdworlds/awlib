
#include "hrcLightNode.h"
#include "../../Internal/hrcInternalsManager.h"

namespace hrengin
{
namespace graphics
{

	hrcLightNode::hrcLightNode()
	//	: 
	{		
		node = __HRIM.videomgr->GetSceneMgr()->addLightSceneNode(0, irr::core::vector3df(100,1000,100), irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);
	}
	
	void hrcLightNode::AttachToEntity(hriBaseEntity* attach)
	{

	}

	void hrcLightNode::SetPosition(Vectorf3d pos)
	{

	}
	void hrcLightNode::SetRotation(Vectorf3d rot)
	{

	}
	void hrcLightNode::SetScale(Vectorf3d scale)
	{

	}
}
}