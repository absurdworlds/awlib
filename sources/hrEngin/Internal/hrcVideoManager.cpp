
#include "hrcVideoManager.h"
#include "../Graphics/Nodes/hrcVisNode.h"
#include "../Graphics/Nodes/hrcCameraNode.h"
#include "hrFilesystem.h"

#include <Irrlicht.h>


namespace hrengin
{
namespace graphics
{

//! default constructor
//! inits all the requried 
hrcVideoManager::hrcVideoManager()
{
	device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600), 32, false, false, true, 0);

	/*if (device == 0)
	{
		throw something;
	}*/

	device->setWindowCaption(L"hrEngine - Irrlicht 1.8.1");
	
	driver = device->getVideoDriver();
	scnmgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
}

hrcVideoManager::~hrcVideoManager() 
{
	device->drop();
};

// currently unused
void hrcVideoManager::CreateScene()
{
	/*irr::scene::ICameraSceneNode* node = 
	irr::scene::ISceneNodeAnimatorCameraRTS* animator 
	animator->drop();
	

	irr::scene::ILightSceneNode* light1 =	scnmgr->addLightSceneNode(0, irr::core::vector3df(100,1000,100), irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);
	irr::scene::IAnimatedMesh* mesh = scnmgr->getMesh(irr::io::path("..\\data\\models\\ground.obj"));
	scnmgr->setAmbientLight(irr::video::SColorf(0.35f,0.35f,0.35f,0.35f));

	irr::scene::IAnimatedMeshSceneNode* nodu = scnmgr->addAnimatedMeshSceneNode( mesh );

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

bool hrcVideoManager::Draw()
{
	if(device->run())
	{
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

			scnmgr->drawAll();
			guienv->drawAll();	

			driver->endScene();
		}
		else
		{
			device->yield();
		}

		return true;
	}
	else
	{
		return false;
	}
}


void hrcVideoManager::AddNode(hriSceneNode& node)
{

}

hriVisNode* hrcVideoManager::CreateVisObject()
{
	return new hrcVisNode(this);
}

hriCameraNode* hrcVideoManager::CreateCamera()
{
	return new hrcCameraNode(this);
}

 hriLightNode* hrcVideoManager::CreateLight()
{
	return nullptr;

}
 
irr::scene::IAnimatedMesh* hrcVideoManager::LoadMesh(const char* modelname)
{
	return scnmgr->getMesh(filesystem::modelpath + modelname);
}

irr::scene::ISceneManager* hrcVideoManager::GetSceneMgr() const
{
	return scnmgr;
}

irr::IrrlichtDevice*  hrcVideoManager::GetDeviceTemporary() const
{
	return device;
}
} // namespace graphics
} // namespace hrengin
