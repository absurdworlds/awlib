/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CLightNode_
#define _hrengin_CLightNode_

//TODO: move to .cpp
#include <irrlicht/irrlicht.h>

#include <hrengin/game/IBaseEntity.h>

#include <hrengin/scene/ILightNode.h>

namespace hrengin {
namespace scene {
class CSceneManager;
class CIrrDummyNode;

class CLightNode : public ILightNode {
public:
	CLightNode(CSceneManager* sceneManager,
		irr::scene::ILightSceneNode* lightNode);
	virtual ~CLightNode();
protected:
	CIrrDummyNode* dummy_;
	irr::scene::ILightSceneNode* node_;
};

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CLightNode_
