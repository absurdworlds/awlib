/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_LightNode_
#define _hrengin_LightNode_

#include <hrengin/scene/LightNode.h>

namespace irr {
namespace scene {
class LightSceneNode;
}
}

namespace hrengin {
namespace scene {
class SceneManager;
class IrrDummyNode;

class LightNode : public LightNode {
public:
	LightNode (SceneManager* sceneManager,
		irr::scene::ILightSceneNode* lightNode);
	virtual ~LightNode ();
protected:
	IrrDummyNode* dummy_;
	irr::scene::ILightSceneNode* node_;
};

} // namespace graphics
} // namespace hrengin
#endif//_hrengin_LightNode_
