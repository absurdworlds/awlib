/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ISceneManager_
#define _hrengin_ISceneManager_

namespace hrengin {
class IEntity;
namespace graphics {
class IMesh;
}
namespace scene {
class INode;
class IEntityNode;
class IVisNode;
class ICameraNode;
class ILightNode;

//! This class manages scene graph
class ISceneManager {
public:
	virtual ~ISceneManager() {};

	//virtual bool step() = 0;

	//! Initialize a new scene, clearing current scene
	virtual void createScene() = 0;
	virtual void drawScene() = 0;
	virtual void update() = 0;

	//virtual IVisNode* createMeshSceneNode(IMesh* mesh) = 0;
	virtual IVisNode* createMeshSceneNode(const char* meshname) = 0;
	virtual ICameraNode* createCameraSceneNode() = 0;
	virtual ILightNode* createLightSceneNode() = 0;
	virtual IEntityNode* createEntitySceneNode(IEntity* entity) = 0;
};

} // namespace scene
} // namespace hrengin

#endif//_hrengin_ISceneManager_
