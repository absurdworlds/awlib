#include <Irrlicht/Irrlicht.h>
//#include <Irrlicht/SAnimatedMesh.h>


#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CSceneManager.h"
#include "CRenderingDevice.h"
#include "CGuiManager.h"

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
	guiManager_ = new gui::CGUIManager(device_->getGUIEnvironment(), device_);

	//platformdata_.win32.wndHandle = device_->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd;
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


gui::IGUIManager* CVideoManager::getGUIManager() const
{
	return guiManager_;
}

u32 CVideoManager::getTime()
{
	static irr::ITimer* timer(device_->getTimer());
	return timer->getTime();
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
void CVideoManager::setWindowCaption(std::wstring newCaption)
{
	caption_ = newCaption.c_str();
}

void CVideoManager::updateCaption()
{
	irr::core::stringw addStr = "";
	if(showFps_) {
		static int lastFPS = -1;
		int fps = driver->getFPS();

		static irr::core::stringw fpsStr;

		if (lastFPS != fps) {
			fpsStr = L"[FPS: ";
			fpsStr += fps;
			fpsStr += "] ";
		}
		
		addStr += fpsStr;
	}
	
	//	str += driver->getName();
	
	device->setWindowCaption((caption + addStr).c_str());
}

void CVideoManager::showCaptionFPS(bool showFps)
{
	showFps_ = showFps;
}
#endif


/*void CVideoManager::drawVertexListObject(std::vector<Vector3d<f32>>& vert, std::vector<u32>& idxs)
{

	this->driver->drawVertexPrimitiveList();

}*/


} // namespace graphics
} // namespace hrengin
