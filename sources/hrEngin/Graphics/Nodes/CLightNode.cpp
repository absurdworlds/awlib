
#include "CLightNode.h"
#include "../../Common/CInternalsManager.h"

namespace hrengin
{
namespace graphics
{

	CLightNode::CLightNode()
	//	: 
	{		
		node = __HRIM.videomgr->GetSceneMgr()->addLightSceneNode(0, irr::core::vector3df(100,1000,100), irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);
	}
	
	void CLightNode::AttachToEntity(IBaseEntity* attach)
	{

	}

	void CLightNode::setPosition(Vector3d pos)
	{

	}
	void CLightNode::setRotation(Vector3d rot)
	{

	}
}
}