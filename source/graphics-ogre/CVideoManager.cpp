/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <random>
#include <string>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRenderSystem.h>
//#include <OGRE/ogrePlatformManager.h>

#include <hrengin/common/config.h>
#include <hrengin/core/ISettingsManager.h>

#include "CVisNode.h"
#include "CCameraNode.h"
#include "CLightNode.h"

#include "CSceneManager.h"
#include "CRenderingDevice.h"
#include "CGuiManager.h"

#include "CVideoManager.h"

#ifdef _HR_ØINDOWS
#include <Windows.h>
#endif

namespace hrengin {
namespace graphics {

IVideoManager* createVideoManager(core::ISettingsManager* settings)
{
	return new CVideoManager(settings);
}

CVideoManager::CVideoManager(core::ISettingsManager* settings)
{
	//ogreRoot_ = new Ogre::Root("plugins.cfg","ogre.cfg","./logs/ogre.log");
	ogreRoot_ = new Ogre::Root("","","./logs/ogre.log");
	
	
	configure(settings);
	setWindow(settings);
	
	window_ = ogreRoot_->initialise(true, "hrengin A-3");
	renderer_ = new CRenderingDevice(ogreRoot_);
	sceneManager_ = new CSceneManager(ogreRoot_, renderer_);
	guiManager_ = new gui::CGUIManager(ogreRoot_, settings);

}

void CVideoManager::configure(core::ISettingsManager* settings)
{
#if 0
	ogreRoot_->loadPlugin("Plugin_ParticleFX");
	ogreRoot_->loadPlugin("Plugin_CgProgramManager");
	ogreRoot_->loadPlugin("Plugin_OctreeSceneManager");
	ogreRoot_->loadPlugin("Plugin_PCZSceneManager");
	ogreRoot_->loadPlugin("Plugin_OctreeZone");
	ogreRoot_->loadPlugin("Plugin_BSPSceneManager");
#endif
	ogreRoot_->loadPlugin("RenderSystem_GL");

	i32 resolutionX = 1066;
	i32 resolutionY = 600;
	bool foolscreen = false;
	if(settings) {
		settings->getValue("graphics.resolutionX",resolutionX);
		settings->getValue("graphics.resolutionY",resolutionY);
		settings->getValue("graphics.fullscreen",foolscreen);
	}

	Ogre::RenderSystemList::const_iterator renderers = ogreRoot_->getAvailableRenderers().begin();

	while(renderers != ogreRoot_->getAvailableRenderers().end()) {
		Ogre::String rName = (*renderers)->getName();

		if (rName == "OpenGL Rendering Subsystem") {
			break;
		}

		renderers++;
	}

	Ogre::RenderSystem *renderSystem = *renderers;
	renderSystem->setConfigOption("Full Screen",foolscreen ? "Yes" : "No");
	std::string videoMode = std::to_string(resolutionX) + " x "
		+ std::to_string(resolutionY) + " @ 32-bit colour";
	renderSystem->setConfigOption("Video Mode", videoMode.c_str());
	renderSystem->setConfigOption("Display Frequency","60 Hz");
	renderSystem->setConfigOption("FSAA","0");
	renderSystem->setConfigOption("Fixed Pipeline Enabled","Yes");
	renderSystem->setConfigOption("RTT Preferred Mode","FBO");
	renderSystem->setConfigOption("VSync","No");
	renderSystem->setConfigOption("sRGB Gamma Conversion","No");

	ogreRoot_->setRenderSystem(renderSystem); 
}


void CVideoManager::setWindow(core::ISettingsManager* settings)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	void* wndHandle;
	window_->getCustomAttribute("WINDOW", &wndHandle);

#if 0
	LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
	SetClassLong( (HWND)wndHandle, GCL_HICON, iconID );
#endif

	settings->setValue("platform.win32.wndHandle", reinterpret_cast<i32>(wndHandle));
#endif
}

CVideoManager::~CVideoManager() 
{
	delete ogreRoot_;
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
	return 0;
}

bool CVideoManager::step()
{
	window_->update();
	return true;
}

void CVideoManager::wait()
{
}

bool CVideoManager::isWindowActive()
{
	return window_->isActive();
}

#if 0
void CVideoManager::setWindowCaption(std::wstring newCaption)
{
	caption_ = newCaption.c_str();
}

void CVideoManager::updateCaption()
{
}

void CVideoManager::showCaptionFPS(bool showFps)
{
	showFps_ = showFps;
}
#endif

} // namespace graphics
} // namespace hrengin
