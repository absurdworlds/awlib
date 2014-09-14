/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CSceneManager_
#define _hrengin_CSceneManager_

#include <vector>

#include <hrengin/common/api.h>
#include <hrengin/common/Vector3d.h>

#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IRenderingDevice.h>
#include <hrengin/graphics/ISceneNode.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/ILightNode.h>

namespace Ogre {
class Root;
class SceneManager;
}

namespace hrengin {
namespace graphics {

class CSceneManager : public ISceneManager {
public:
	CSceneManager(Ogre::Root* ogreRoot, IRenderingDevice* renderer);

	virtual void createScene();

	virtual void drawScene();

	virtual void update();
	
	virtual IVisNode* createMeshSceneNode(const char* meshname);
	//virtual IVisNode* createMeshSceneNode(IMesh* mesh);
	virtual ICameraNode* createCameraSceneNode();
	virtual ILightNode* createLightSceneNode();
private:
	std::vector<ISceneNode*> NodeList;
	
	Ogre::Root* ogreRoot_;
	Ogre::SceneManager* scnMgr_;
};

ISceneManager* createSceneManager();

} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CSceneManager_
