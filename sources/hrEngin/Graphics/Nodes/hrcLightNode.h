
#ifndef __HG_hrcLightNode__
#define __HG_hrcLightNode__

#include <Graphics/Nodes/hriLightNode.h>
#include <Graphics/Base/hriVideoManager.h>
#include <Base/Entities/hriBaseEntity.h>

#include <Irrlicht.h>

namespace hrengin
{
namespace graphics
{
	

class hrcLightNode : public hriLightNode
{
	public:
		hrcLightNode();

		virtual void AttachToEntity(hriBaseEntity* attach);

		virtual void SetPosition(Vectorf3d pos);
		virtual void SetRotation(Vectorf3d rot);
		virtual void SetScale(Vectorf3d scale);
	protected:
		hriBaseEntity* attachedTo;

		irr::scene::ILightSceneNode* node;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_hrcLightNode__