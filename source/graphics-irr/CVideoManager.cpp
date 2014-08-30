#include <Irrlicht/Irrlicht.h>
//#include <Irrlicht/SAnimatedMesh.h>


#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CSceneManager.h"
#include "CRenderingDevice.h"

#include "CVideoManager.h"


namespace hrengin {
namespace graphics {

IVideoManager* createVideoManager()
{
	return new CVideoManager();
}

CVideoManager::CVideoManager()
{
	device_ = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1066, 600), 32, false, false, true, 0);

	device_->setWindowCaption(L"hrengin A - Irrlicht 1.8.1");

	renderer_ = new CRenderingDevice(device_->getVideoDriver());
	sceneManager_ = new CSceneManager(device_->getSceneManager(), renderer_, device_);

	//guienv = device->getGUIEnvironment();

	platformdata_.win32.wndHandle = device_->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd;
}

CVideoManager::~CVideoManager() 
{
	device_->drop();
};


IRenderingDevice* CVideoManager::getRenderingDevice() const
{
	return renderer_;
}

ISceneManager* CVideoManager::getSceneManager() const
{
	return sceneManager_;
}

PlatformData CVideoManager::getPlatformSpecificData() const
{
	return platformdata_;
}

bool CVideoManager::step()
{
	if (device_->run()) {
		return true;
	} else {
		return false;
	}
}

void CVideoManager::wait()
{
	device_->yield();
}

bool CVideoManager::isWindowActive()
{
	return device_->isWindowActive();
}

#if 0

void CVideoManager::end()
{

	 
	device->yield();
}
#endif


/*void CVideoManager::drawVertexListObject(std::vector<Vectorf3d>& vert, std::vector<u32>& idxs)
{

	this->driver->drawVertexPrimitiveList();

}*/


} // namespace graphics
} // namespace hrengin
