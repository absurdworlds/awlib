/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_VisNode_
#define _aw_VisNode_

#include <aw/common/types.h>

#include <aw/graphics/Mesh.h>
#include <aw/scene/VisNode.h>

namespace irr {
namespace scene {
class AnimatedMeshSceneNode;
}
}

namespace aw {
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
} // namespace aw
#endif//_aw_VisNode_
