
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

IBaseEntity* CCameraNode::castRayFromScreen(hrengin::i32 x, hrengin::i32 y)
{
	irr::scene::ISceneCollisionManager* colman = __HRIM.videomgr->getCollManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), node);
	irr::core::plane3df plane(node->getViewFrustum()->planes[irr::scene::SViewFrustum::VF_FAR_PLANE]);
	irr::core::vector3df vec;
	
	plane.getIntersectionWithLine(line.start, line.getVector(), vec);
	Vectorf3d end(vec.X,
				  vec.Y,
				  vec.Z);
	Vectorf3d start(end.X,
				   50.,
				   end.Z);
	/*printf("--mous--\n");
	printf("%d\n",x);
	printf("%d\n",y);
	printf("--line--\n");
	printf("%.5f\n",start.X);
	printf("%.5f\n",start.Y);
	printf("%.5f\n",start.Z);
	printf("--end--\n");
	printf("%.5f\n",end.X);
	printf("%.5f\n",end.Y);
	printf("%.5f\n",end.Z);*/

	if(__HRIM.physmgr->castRay(start, end))
	{
		printf("!\n");
		/*
		printf("%d\n",__HRIM.physmgr);
		printf("%d\n",__HRIM.physmgr->castRay(start, end));*/
		return __HRIM.physmgr->castRay(start, end)->getEntity();
	};
	
	return 0;
	
}

void CCameraNode::setPosition(Vector3d pos)
{

}
void CCameraNode::setRotation(Vector3d rot)
{

}

void CCameraNode::SetDistance(f64 dist)
{

}

void CCameraNode::SetTargetPosition(Vector3d pos)
{

}
void CCameraNode::SetCameraPosition(Vector3d pos)
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