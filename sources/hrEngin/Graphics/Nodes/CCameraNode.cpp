
#include "CCameraNode.h"
#include "../IrrExt/CSceneNodeAnimatorCameraRTS.h"
#include "../../Common/CInternalsManager.h"

namespace hrengin
{
namespace graphics
{
	
//! constructor
//!
CCameraNode::CCameraNode()
	:controlBehavior(CAM_NONE)
{
	node = __HRIM.videomgr->GetSceneMgr()->addCameraSceneNode(0, irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));
}

//! constructor
//! Attaches node to entity
CCameraNode::CCameraNode(IBaseEntity* attach)
	: attachedTo(attach), controlBehavior(CAM_NONE)
{
	node = __HRIM.videomgr->GetSceneMgr()->addCameraSceneNode(0, irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));	
}

void CCameraNode::AttachToEntity(IBaseEntity* attach)
{

}

void CCameraNode::SetPosition(Vectorf3d pos)
{

}
void CCameraNode::SetRotation(Vectorf3d rot)
{

}
void CCameraNode::SetScale(Vectorf3d scale)
{

}

void CCameraNode::SetDistance(f64 dist)
{

}

void CCameraNode::SetTargetPosition(Vectorf3d pos)
{

}
void CCameraNode::SetCameraPosition(Vectorf3d pos)
{

}

void CCameraNode::BindTargetToCamera(bool bind)
{

}

void CCameraNode::SetCameraFOV(f64 fov)
{

}
void CCameraNode::SetNearPlane(f64 dist)
{

}
void CCameraNode::SetFarPlane(f64 dist)
{

}

void CCameraNode::SetBehavior(CAM_Behavior beh)
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