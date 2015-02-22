/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_VisNode_
#define _hrengin_VisNode_

#include <hrengin/common/types.h>

#include <hrengin/graphics/Mesh.h>
#include <hrengin/scene/VisNode.h>

namespace irr {
namespace scene {
class AnimatedMeshSceneNode;
}
}

namespace hrengin {
namespace scene {
class SceneManager;
class IrrDummyNode;

class VisNode : public VisNode {
public:
	VisNode (SceneManager* sceneManager,
		irr::scene::IAnimatedMeshSceneNode* meshNode);
	virtual ~VisNode ();

	//virtual void setMesh(Mesh* mesh);
	virtual void setMesh (char const* mesh);

private:
	SceneManager* sceneManager_;

	IrrDummyNode* dummy_;
	irr::scene::IAnimatedMeshSceneNode* meshNode_;
};

} // namespace scene
} // namespace hrengin
#endif//_hrengin_VisNode_
