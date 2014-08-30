
#include <Irrlicht/ISceneManager.h>
#include <Irrlicht/ISceneCollisionManager.h>


#include <hrengin/core/hrenginpaths.h>

#include "CCameraNode.h"
#include "CLightNode.h"
#include "CVisNode.h"
#include "CSceneManager.h"


namespace hrengin {
namespace graphics {

CSceneManager::CSceneManager(irr::scene::ISceneManager* irrSceneManager, IRenderingDevice* renderer, irr::IrrlichtDevice* device)
: scnmgr(irrSceneManager), colman(scnmgr->getSceneCollisionManager()), device_(device)
{

}

void CSceneManager::createScene()
{
	/*
	irr::scene::IAnimatedMesh* mesh = scnmgr->getMesh(irr::io::path("..\\data\\models\\ground.obj"));
	scnmgr->setAmbientLight(irr::video::SColorf(0.35f,0.35f,0.35f,0.35f));
	
	// cleanup later
	irr::video::IImage *teal = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *blue = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *red  = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));

	teal->fill(irr::video::SColor(130, 0, 255, 255));
	blue->fill(irr::video::SColor(130, 0, 0, 255));
	red->fill(irr::video::SColor(64, 255, 0, 0));
	
	device->getVideoDriver()->addTexture("teal", teal);
	device->getVideoDriver()->addTexture("blue", blue);
	device->getVideoDriver()->addTexture("red", red);*/
}

void CSceneManager::update()
{

}

//IVisNode* CSceneManager::createMeshSceneNode(IMesh* mesh)
IVisNode* CSceneManager::createMeshSceneNode(const char* meshname)
{
	irr::scene::IAnimatedMeshSceneNode* node = 
		scnmgr->addAnimatedMeshSceneNode(convertMesh(meshname));
	return new CVisNode(this, node);
}

ICameraNode* CSceneManager::createCameraSceneNode()
{
	irr::scene::ICameraSceneNode* node = scnmgr->addCameraSceneNode(0,
		irr::core::vector3df(0, 0, 0),
		irr::core::vector3df(0, 0, 0));
	return new CCameraNode(this, node, scnmgr, device_);
}

ILightNode* CSceneManager::createLightSceneNode()
{
	irr::scene::ILightSceneNode* node = scnmgr->addLightSceneNode(0,
		irr::core::vector3df(100, 1000, 100),
		irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);
	return new CLightNode(this, node);
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

} // namespace graphics
} // namespace hrengin
