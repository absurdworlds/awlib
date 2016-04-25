/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_SceneManager_
#define _aw_SceneManager_
#include <vector>

#include <aw/math/Vector3d.h>

#include <aw/graphics/RenderingDevice.h>

#include <aw/scene/scene.h>
#include <aw/scene/SceneManager.h>
#include <aw/scene/VisNode.h>
#include <aw/scene/CameraNode.h>
#include <aw/scene/LightNode.h>
#include <aw/scene/EntityNode.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class SceneManager;
class AnimatedMesh;
class SceneCollisionManager;
class SceneNode;
}
}

namespace aw {
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
} // namespace aw
#endif//_aw_SceneManager_
