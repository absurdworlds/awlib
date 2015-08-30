/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_SceneManager_
#define _awrts_SceneManager_

#include <vector>

#include <awrts/math/Vector3d.h>

#include <awrts/graphics/RenderingDevice.h>

#include <awrts/scene/scene.h>
#include <awrts/scene/SceneManager.h>
#include <awrts/scene/VisNode.h>
#include <awrts/scene/CameraNode.h>
#include <awrts/scene/LightNode.h>
#include <awrts/scene/EntityNode.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class SceneManager;
class AnimatedMesh;
class SceneCollisionManager;
class SceneNode;
}
}

namespace awrts {
namespace scene {
//! Class to manage the scene graph
class SceneManager : public SceneManager {
public:
	SceneManager(irr::scene::ISceneManager* irrSceneManager,
		graphics::RenderingDevice* renderer,
		irr::IrrlichtDevice* device);

	virtual void createScene();

	virtual void drawScene();

	virtual void update();

	virtual VisNode* createMeshSceneNode(char const* meshname);
	//virtual VisNode* createMeshSceneNode(Mesh* mesh);
	virtual CameraNode* createCameraSceneNode();
	virtual LightNode* createLightSceneNode();
	virtual EntityNode* createEntitySceneNode(Entity* entity);
private:
	std::vector<Node*> NodeList;
	
	irr::IrrlichtDevice* device_;
	irr::scene::ISceneManager*          scnmgr;
	irr::scene::ISceneCollisionManager* colman;
public:
	irr::scene::IAnimatedMesh* convertMesh(char* const meshname);
	//irr::scene::IAnimatedMesh* convertMesh(IMesh* mesh);
};

} // namespace graphics
} // namespace awrts
#endif//_awrts_SceneManager_
