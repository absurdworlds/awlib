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

#include <awrts/core/SettingsManager.h>

#include "VisNode.h"
#include "CameraNode.h"
#include "LightNode.h"

#include "SceneManager.h"
#include "RenderingDevice.h"
#include "GuiManager.h"

#include "VideoManager.h"

namespace awrts {
namespace graphics {

VideoManager* createVideoManager(core::SettingsManager* settings)
{
	return new VideoManager(settings);
}

VideoManager::VideoManager(core::SettingsManager* settings)
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

	device_->setWindowCaption(L"awrts A - Irrlicht 1.8.1");

	renderer_ = new RenderingDevice(device_->getVideoDriver());
	sceneManager_ = new scene::SceneManager(device_->getSceneManager(), renderer_, device_);
	guiManager_ = new gui::GUIManager(device_->getGUIEnvironment(), device_);

#ifdef HR_WINDOWS
	settings->setValue("platform.win32.wndHandle", reinterpret_cast<i32>(device_->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd));
#endif
}

VideoManager::~VideoManager() 
{
	device_->drop();
};


RenderingDevice* VideoManager::getRenderingDevice() const
{
	return renderer_;
}

scene::SceneManager* VideoManager::getSceneManager() const
{
	return sceneManager_;
}


gui::GUIManager* VideoManager::getGUIManager() const
{
	return guiManager_;
}

u32 VideoManager::getTime()
{
	static irr::ITimer* timer(device_->getTimer());
	return timer->getTime();
}

bool VideoManager::step()
{
	if (device_->run()) {
		return true;
	} else {
		return false;
	}
	
}

void VideoManager::wait()
{
	device_->yield();
}

bool VideoManager::isWindowActive()
{
	return device_->isWindowActive();
}

#if 0
void VideoManager::setWindowCaption(std::wstring newCaption)
{
	caption_ = newCaption.c_str();
}

void VideoManager::updateCaption()
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

void VideoManager::showCaptionFPS(bool showFps)
{
	showFps_ = showFps;
}
#endif

} // namespace graphics
} // namespace awrts
