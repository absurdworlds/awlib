#include <Irrlicht/Irrlicht.h>

#include <hrengin/core/hrenginpaths.h>

#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CVideoManager.h"

namespace hrengin {
namespace graphics {

IVideoManager* createVideoManager()
{
	return new CVideoManager();
}

CVideoManager::CVideoManager()
{
	device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1066, 600), 32, false, false, true, 0);

	/*if (device == 0) {
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

bool CVideoManager::step()
{
	if (device->run()) {
		device->yield();
		return true;
	} else {
		return false;
	}
}

bool CVideoManager::isWindowActive()
{
	return device->isWindowActive();
}

#if 0
irr::scene::IAnimatedMesh* CVideoManager::LoadMesh(const char* modelname)
{
	std::string path = io::modelpath + modelname;
	return scnmgr->getMesh(path.c_str());
}

void CVideoManager::ll1()
{
/*	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	driver->setMaterial(debugMat);
	driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
*/
}

void CVideoManager::end()
{
	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	driver->setMaterial(debugMat);
	driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);

	 
	device->yield();
}
#endif


/*void CVideoManager::drawVertexListObject(std::vector<Vectorf3d>& vert, std::vector<u32>& idxs)
{

	this->driver->drawVertexPrimitiveList();

}*/


} // namespace graphics
} // namespace hrengin
