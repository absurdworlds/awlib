/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <random>
#include <string>

#include <Irrlicht/irrlicht.h>

#include <hrengin/core/ISettingsManager.h>

#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CSceneManager.h"
#include "CRenderingDevice.h"
#include "CGuiManager.h"

#include "CVideoManager.h"

namespace hrengin {
namespace graphics {

IVideoManager* createVideoManager(core::ISettingsManager* settings)
{
	return new CVideoManager(settings);
}

CVideoManager::CVideoManager(core::ISettingsManager* settings)
{
	i32 resolutionX = 1066;
	i32 resolutionY = 600;
	bool fullscreen = false;
	if(settings) {
		settings->getValue("graphics.resolutionX",resolutionX);
		settings->getValue("graphics.resolutionY",resolutionY);
		settings->getValue("graphics.fullscreen",fullscreen);
	}
	device_ = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(resolutionX, resolutionY), 32, fullscreen, true, true, 0);

	device_->setWindowCaption(L"hrengin A - Irrlicht 1.8.1");

	renderer_ = new CRenderingDevice(device_->getVideoDriver());
	sceneManager_ = new scene::CSceneManager(device_->getSceneManager(), renderer_, device_);
	guiManager_ = new gui::CGUIManager(device_->getGUIEnvironment(), device_);

#ifdef HR_WINDOWS
	settings->setValue("platform.win32.wndHandle", reinterpret_cast<i32>(device_->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd));
#endif
}

CVideoManager::~CVideoManager() 
{
	device_->drop();
};


IRenderingDevice* CVideoManager::getRenderingDevice() const
{
	return renderer_;
}

scene::ISceneManager* CVideoManager::getSceneManager() const
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
	
		str += driver->getName();
	
	device->setWindowCaption((caption + addStr).c_str());
}

void CVideoManager::showCaptionFPS(bool showFps)
{
	showFps_ = showFps;
}
#endif

} // namespace graphics
} // namespace hrengin
