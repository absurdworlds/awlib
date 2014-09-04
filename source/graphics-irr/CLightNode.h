#ifndef __HG_CLightNode__
#define __HG_CLightNode__

#include <Irrlicht/Irrlicht.h>

#include <hrengin/graphics/ILightNode.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/game/IBaseEntity.h>

namespace hrengin {
namespace graphics {
class CSceneManager;

class CLightNode : public ILightNode {
public:
	CLightNode(CSceneManager* sceneManager,
		irr::scene::ILightSceneNode* lightNode);
		
	virtual void setParentEntity(IBaseEntity* parent);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);
	//virtual void SetScale(Vector3d<f32> scale);
protected:
	IBaseEntity* attachedTo;

	irr::scene::ILightSceneNode* node_;
};

	
} // namespace graphics
} // namespace hrengin

#endif//__HG_CLightNode__