/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Irrlicht/ISceneManager.h>
#include <Irrlicht/ISceneCollisionManager.h>


#include <hrengin/core/paths.h>

#include "CCameraNode.h"
#include "CLightNode.h"
#include "CVisNode.h"
#include "CSceneManager.h"

namespace hrengin {
namespace scene {

CSceneManager::CSceneManager(irr::scene::ISceneManager* irrSceneManager,
	graphics::IRenderingDevice* renderer,
	irr::IrrlichtDevice* device)
: scnmgr(irrSceneManager), colman(scnmgr->getSceneCollisionManager()), device_(device)
{

}

void CSceneManager::createScene()
{
	//TODO: global lighting manager?
	scnmgr->setAmbientLight(irr::video::SColorf(0.35f,0.35f,0.35f,0.35f));
#if 0
	
	// cleanup later
	irr::video::IImage *teal = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *blue = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *red  = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));

	teal->fill(irr::video::SColor(130, 0, 255, 255));
	blue->fill(irr::video::SColor(130, 0, 0, 255));
	red->fill(irr::video::SColor(64, 255, 0, 0));
	
	device->getVideoDriver()->addTexture("teal", teal);
	device->getVideoDriver()->addTexture("blue", blue);
	device->getVideoDriver()->addTexture("red", red);
#endif
}

void CSceneManager::update()
{

}

//IVisNode* CSceneManager::createMeshSceneNode(IMesh* mesh)
IVisNode* CSceneManager::createMeshSceneNode(const char* meshname)
{
	irr::scene::IAnimatedMeshSceneNode* node = 
		scnmgr->addAnimatedMeshSceneNode(convertMesh(meshname));
	
	if(std::string(meshname) == "sotank.obj") {
		node->addShadowVolumeSceneNode();
	}

	IVisNode* newNode = new CVisNode(this, node);

	return newNode;
}

ICameraNode* CSceneManager::createCameraSceneNode()
{
	irr::scene::ICameraSceneNode* node = scnmgr->addCameraSceneNode(0,
		irr::core::vector3df(0, 0, 0),
		irr::core::vector3df(0, 0, 0));

	node->setPosition(irr::core::vector3df(100,100,100));

	ICameraNode* newNode = new CCameraNode(this, node, scnmgr, device_);

	return newNode;
}

ILightNode* CSceneManager::createLightSceneNode()
{
	irr::scene::ILightSceneNode* node = scnmgr->addLightSceneNode(0,
		irr::core::vector3df(100, 1000, 100),
		irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);

	ILightNode* newNode = new CLightNode(this, node);

	return newNode;
}


IEntityNode* CSceneManager::createEntitySceneNode(IEntity* entity)
{
	return 0;
}

void CSceneManager::drawScene()
{
	scnmgr->drawAll();
}

//irr::scene::IAnimatedMesh* CVideoManager::LoadMesh(const char* modelname)
irr::scene::IAnimatedMesh* CSceneManager::convertMesh(const char* modelname)
{
	std::string path = io::modelpath + modelname;
	return scnmgr->getMesh(path.c_str());
}

} // namespace scene
} // namespace hrengin
