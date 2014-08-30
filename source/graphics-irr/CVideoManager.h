#ifndef _hrengin_CVideoManager_
#define _hrengin_CVideoManager_

#include <vector>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/graphics/ISceneManager.h>
#include <hrengin/graphics/IRenderingDevice.h>

#include "CVisNode.h"

namespace irr {
class IrrlichtDevice;

namespace video {
	class IVideoDriver;
}

namespace scene {
	class ISceneManager;
	class IAnimatedMesh;
	class ISceneCollisionManager;
}

}

namespace hrengin {
	class CEncore;

namespace gui {
	class CGUIManager;
}



/*
//TODO: later move t set caption func
static int lastFPS = -1;
int fps = driver->getFPS();

if (lastFPS != fps)  
{
	irr::core::stringw str = L"hEengin - Irrlicht 1.8.1 DEBUG ["; //later move tosrt caption func
	str += driver->getName();
	str += "] FPS:";
	str += fps;

	device->setWindowCaption(str.c_str());
	lastFPS = fps;
}
// end todo*/

namespace graphics {

class CVisNode;

class CVideoManager : public IVideoManager {
friend class CEncore;
friend class CGUIManager;
public:
	CVideoManager();
	virtual ~CVideoManager();
	
	virtual bool step();
	virtual void wait();

	virtual bool isWindowActive();
	

	virtual IRenderingDevice* getRenderingDevice() const;
	virtual ISceneManager* getSceneManager() const;

	virtual PlatformData getPlatformSpecificData() const;

	virtual IMesh* loadMesh(const char * modelname);


private:
	irr::IrrlichtDevice* device_;

	ISceneManager* sceneManager_;
	IRenderingDevice* renderer_;
	//IGUIManager* guiManager_;

	PlatformData platformdata_;

};
	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CVideoManager_