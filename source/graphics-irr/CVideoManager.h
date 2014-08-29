#ifndef _hrengin_CVideoManager_
#define _hrengin_CVideoManager_

#include <vector>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/graphics/ISceneNode.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>
#include <hrengin/graphics/ILightNode.h>

#include "CVisNode.h"
#include <Irrlicht/SAnimatedMesh.h>

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

	virtual bool isWindowActive();

	virtual PlatformData getPlatformSpecificData() const;


	virtual irr::scene::IAnimatedMesh* LoadMesh(const char * modelname);


private:
	irr::IrrlichtDevice*			device;

	PlatformData platformdata_;

};
	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_CVideoManager_