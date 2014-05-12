
#include "hrcCameraNode.h"
#include "../IrrExt/CSceneNodeAnimatorCameraRTS.h"
#include "../../Internal/hrcInternalsManager.h"

namespace hrengin
{
namespace graphics
{
	
//! constructor
//!
hrcCameraNode::hrcCameraNode()
	:controlBehavior(CAM_NONE)
{
	node = __HRIM.videomgr->GetSceneMgr()->addCameraSceneNode(0, irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));
}

//! constructor
//! Attaches node to entity
hrcCameraNode::hrcCameraNode(hriBaseEntity* attach)
	: attachedTo(attach), controlBehavior(CAM_NONE)
{
	node = __HRIM.videomgr->GetSceneMgr()->addCameraSceneNode(0, irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));	
}

void hrcCameraNode::AttachToEntity(hriBaseEntity* attach)
{

}

void hrcCameraNode::SetPosition(Vectorf3d pos)
{

}
void hrcCameraNode::SetRotation(Vectorf3d rot)
{

}
void hrcCameraNode::SetScale(Vectorf3d scale)
{

}

void hrcCameraNode::SetDistance(f64 dist)
{

}

void hrcCameraNode::SetTargetPosition(Vectorf3d pos)
{

}
void hrcCameraNode::SetCameraPosition(Vectorf3d pos)
{

}

void hrcCameraNode::BindTargetToCamera(bool bind)
{

}

void hrcCameraNode::SetCameraFOV(f64 fov)
{

}
void hrcCameraNode::SetNearPlane(f64 dist)
{

}
void hrcCameraNode::SetFarPlane(f64 dist)
{

}

void hrcCameraNode::SetBehavior(CAM_Behavior beh)
{
	#ifdef _DEBUG
		fprintf(stderr, "DEBUG: function call %s\n", __FUNCTION_NAME__);
	#endif //_DEBUG

	controlBehavior = beh;
	
	/* reset camera animator */
	if(animator)
	{
		node->removeAnimator(animator);
		//animator->drop();
		animator = 0;

	}

	switch(controlBehavior)
	{
		case CAM_STRATEGIC:
			animator = new irr::scene::CSceneNodeAnimatorCameraRTS(__HRIM.videomgr->GetDevice()->getCursorControl(),__HRIM.videomgr->GetDevice()->getTimer()); 
			node->addAnimator(animator);
		break;
		default:
		case CAM_NONE:
			break;
	}
}


	
} // namespace graphics
} // namespace hrengin