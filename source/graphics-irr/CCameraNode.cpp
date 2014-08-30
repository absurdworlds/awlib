
#include <hrengin/common/Line3d.h>

#include "IrrExt/CSceneNodeAnimatorCameraRTS.h"

#include "CVideoManager.h"

#include "CCameraNode.h"

namespace hrengin {
namespace graphics {

CCameraNode::CCameraNode(CSceneManager* sceneManager,
	irr::scene::ICameraSceneNode* camNode,
	irr::scene::ISceneManager* irrScMgr,
	irr::IrrlichtDevice* device)
	: controlBehavior(CAM_NONE), node_(camNode), scmgr_(irrScMgr), device_(device)
{

}

void CCameraNode::setParentEntity(IBaseEntity* parent)
{

}

hrengin::base::line3df CCameraNode::castRayFromScreen(hrengin::i32 x, hrengin::i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), node_);

	//irr::core::plane3df plane(node->getViewFrustum()->planes[irr::scene::SViewFrustum::VF_FAR_PLANE]);
	//irr::core::vector3df vec;
	
	//plane.getIntersectionWithLine(line.start, line.getVector(), vec);
	return line;
}

hrengin::Vector3d CCameraNode::__tempGetRayHitPlaneCoords(hrengin::i32 x, hrengin::i32 y)
{
	irr::scene::ISceneCollisionManager* colman = scmgr_->getSceneCollisionManager();
	irr::core::line3df line = colman->getRayFromScreenCoordinates(irr::core::vector2di(x,y), node_);
	//printf("%d\n",x);
	//printf("%f\n",line.start.X);
	//irr::core::line3df line(10,50,10,10,-50,10);
	irr::core::vector3df vec;
	
	/*hrengin::Vectorf3d start(line.end.X,
				             50,
				             line.end.Z);
	hrengin::Vectorf3d end(line.start.X,
						  0,
				           line.start.Z);
						   */
	//irr::core::plane3df plane(node->getViewFrustum()->planes[irr::scene::SViewFrustum::VF_FAR_PLANE]);
	irr::core::plane3df plane(irr::core::vector3d<f32>(0, 0, 0), irr::core::vector3d<f32>(0, 1, 0));
	//plane.getIntersectionWithLine(ray.getMiddle(),ray.getVector(),out);
	//irr::core::vector3df vec;
	
	plane.getIntersectionWithLine(line.start, line.getVector(), vec);
	return hrengin::Vector3d(vec.X,0,vec.Z);
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
	controlBehavior = beh;
	
	/* reset camera animator */
	if(animator)
	{
		node_->removeAnimator(animator);
		//animator->drop();
		animator = 0;

	}

	switch(controlBehavior)
	{
	case CAM_STRATEGIC:
		animator = new irr::scene::CSceneNodeAnimatorCameraRTS(device_->getCursorControl(), device_->getTimer());
		node_->addAnimator(animator);
		animator->drop();
	break;
	default:
	case CAM_NONE:
		break;
	}
}


	
} // namespace graphics
} // namespace hrengin