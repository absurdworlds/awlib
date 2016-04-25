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

namespace aw {
class Entity;
namespace graphics {
class Mesh;
}
namespace scene {
class Node;
class EntityNode;
class VisNode;
class CameraNode;
class LightNode;

//! This class manages scene graph
class SceneManager {
public:
	//! Virtual destructor
	virtual ~SceneManager()
	{
	}
	//virtual bool step() = 0;

	//! Initialize a new scene, clearing current scene
	virtual void createScene() = 0;
	virtual void drawScene() = 0;
	virtual void update() = 0;

	//virtual VisNode* createMeshSceneNode(Mesh* mesh) = 0;
	virtual VisNode* createMeshSceneNode(char const* meshname) = 0;
	virtual CameraNode* createCameraSceneNode() = 0;
	virtual LightNode* createLightSceneNode() = 0;
	virtual EntityNode* createEntitySceneNode(Entity* entity) = 0;
};

} // namespace scene
} // namespace aw
#endif//_aw_SceneManager_
