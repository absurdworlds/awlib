
#ifndef __HG_CLightNode__
#define __HG_CLightNode__

#include <Graphics/Nodes/ILightNode.h>
#include <Graphics/Base/IVideoManager.h>
#include <Entities/IBaseEntity.h>

#include <Irrlicht/Irrlicht.h>

namespace hrengin
{
namespace graphics
{
	

class CLightNode : public ILightNode
{
	public:
		CLightNode();

		virtual void AttachToEntity(IBaseEntity* attach);

		virtual void setPosition(Vector3d pos);
		virtual void setRotation(Vector3d rot);
		//virtual void SetScale(Vectorf3d scale);
	protected:
		IBaseEntity* attachedTo;

		irr::scene::ILightSceneNode* node;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_CLightNode__