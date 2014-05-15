
#ifndef __HG_hrñCameraNode__
#define __HG_hrñCameraNode__

#include <Graphics/Nodes/ICameraNode.h>
#include <Graphics/Base/IVideoManager.h>
#include <Base/Entities/IBaseEntity.h>

#include <Irrlicht/Irrlicht.h>

namespace hrengin
{
namespace graphics
{



class CCameraNode : public ICameraNode
{
	public:
		CCameraNode();
		CCameraNode(IBaseEntity* attach);

		virtual void AttachToEntity(IBaseEntity* attach);

		virtual void SetPosition(Vectorf3d pos);
		virtual void SetRotation(Vectorf3d rot);
		virtual void SetScale(Vectorf3d scale);

		virtual void SetTargetPosition(Vectorf3d pos);
		virtual void SetCameraPosition(Vectorf3d pos);

		virtual void BindTargetToCamera(bool bind);

		virtual void SetCameraFOV(f64 fov);
		virtual void SetNearPlane(f64 dist);
		virtual void SetFarPlane(f64 dist);

		virtual void SetDistance(f64 dist);

		virtual void SetBehavior(CAM_Behavior beh);
	private:
		IBaseEntity* attachedTo;

		CAM_Behavior controlBehavior;
		
		irr::scene::ICameraSceneNode* node;
		irr::scene::ISceneNodeAnimator* animator;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hrñVisNode__