/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CLightNode_
#define _hrengin_CLightNode_

#include <hrengin/graphics/ILightNode.h>
#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/game/IBaseEntity.h>

namespace Ogre {
class Light;
}

namespace hrengin {
namespace graphics {
class CSceneManager;

class CLightNode : public ILightNode {
public:
	CLightNode(CSceneManager* sceneManager, Ogre::Light* lightNode);

	virtual void setParentEntity(IBaseEntity* parent);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);
	//virtual void SetScale(Vector3d<f32> scale);
protected:
	IBaseEntity* attachedTo;

	Ogre::Light* node_;
};

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CLightNode_
