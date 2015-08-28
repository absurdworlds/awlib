/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_SceneManager_
#define _hrengin_SceneManager_

#include <vector>

#include <hrengin/math/Vector3d.h>

#include <hrengin/graphics/RenderingDevice.h>

#include <hrengin/scene/scene.h>
#include <hrengin/scene/SceneManager.h>
#include <hrengin/scene/VisNode.h>
#include <hrengin/scene/CameraNode.h>
#include <hrengin/scene/LightNode.h>
#include <hrengin/scene/EntityNode.h>

namespace irr {
class IrrlichtDevice;
namespace scene {
class SceneManager;
class AnimatedMesh;
class SceneCollisionManager;
class SceneNode;
}
}

namespace hrengin {
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
} // namespace hrengin
#endif//_hrengin_SceneManager_
