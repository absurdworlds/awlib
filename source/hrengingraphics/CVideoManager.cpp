#include <Irrlicht/Irrlicht.h>

#include <hrengin/filesystem/hrenginpaths.h>

#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CVideoManager.h"

namespace hrengin {
namespace graphics {

HRENGINGRAPHICS_API IVideoManager& getVideoManager()
{
	return getLocalManager();
}

CVideoManager& getLocalManager()
{
	static CVideoManager* singleton = new CVideoManager;
	return *singleton;
}

CVideoManager::CVideoManager()
{
	device = irr::createDevice( irr::video::EDT_DIRECT3D9, irr::core::dimension2d<irr::u32>(1066, 600), 32, false, false, true, 0);

	/*if (device == 0)
	{
		throw something;
	}*/

	device->setWindowCaption(L"hrengin A - Irrlicht 1.8.1");
	driver = device->getVideoDriver();
	scnmgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	colman = scnmgr->getSceneCollisionManager();

	platformdata_.win32.wndHandle = driver->getExposedVideoData().OpenGLWin32.HWnd;
}

CVideoManager::~CVideoManager() 
{
	device->drop();
};

PlatformData CVideoManager::getPlatformSpecificData() const
{
	return platformdata_;
}

// currently unused
void CVideoManager::CreateScene()
{
	/*irr::scene::ICameraSceneNode* node = 
	irr::scene::ISceneNodeAnimatorCameraRTS* animator 
	animator->drop();
	

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

bool CVideoManager::advance()
{
	if (device->run()) {
		device->yield();
		return true;
	} else {
		return false;
	}
}

void CVideoManager::draw()
{
		driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
	//if (device->isWindowActive()) {

		scnmgr->drawAll();
		guienv->drawAll();

	//}
	
}


void CVideoManager::AddNode(ISceneNode& node)
{

}

IVisNode* CVideoManager::CreateVisObject()
{
	return new CVisNode();
}

ICameraNode* CVideoManager::CreateCamera()
{
	return new CCameraNode();
}

 ILightNode* CVideoManager::CreateLight()
{
	return new CLightNode();

}
 
irr::scene::IAnimatedMesh* CVideoManager::LoadMesh(const char* modelname)
{
	std::string path = io::modelpath + modelname;
	return scnmgr->getMesh(path.c_str());
}

irr::scene::ISceneManager* CVideoManager::GetSceneMgr() const
{
	return scnmgr;
}

irr::scene::ISceneCollisionManager* CVideoManager::getCollManager() const
{
	return scnmgr->getSceneCollisionManager();
}

irr::IrrlichtDevice*  CVideoManager::GetDevice() const
{
	return device;
}

void CVideoManager::ll1()
{

   irr::video::SMaterial debugMat;
   debugMat.Lighting = false;

         driver->setMaterial(debugMat);
         driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
	 }

void CVideoManager::end()
{

   irr::video::SMaterial debugMat;
   debugMat.Lighting = false;

         driver->setMaterial(debugMat);
         driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

	 
		driver->endScene();
	device->yield();
	 }
void CVideoManager::drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color)
{

this->driver->draw3DLine(
	irr::core::vector3df(from.X, from.Y, from.Z),
	irr::core::vector3df(to.X, to.Y, to.Z),
	irr::video::SColor(255, (irr::u32)color.X, (irr::u32)color.Y, (irr::u32)color.Z));
}

} // namespace graphics
} // namespace hrengin
