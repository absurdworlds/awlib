/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IVideoManager_
#define _hrengin_IVideoManager_

#include <hrengin/graphics/graphics.h>

#include <hrengin/common/types.h>

namespace hrengin {
namespace core {
class ISettingsManager;
}
namespace gui {
class IGUIManager;
}
namespace scene {
class ISceneManager;
}
namespace graphics {
class IRenderingDevice;

//! Holds other devices and manipuletas the window
class IVideoManager {
public:
	virtual ~IVideoManager ()
	{
	}

	virtual IRenderingDevice* getRenderingDevice () const = 0;
	virtual scene::ISceneManager* getSceneManager () const = 0;
	virtual gui::IGUIManager* getGUIManager () const = 0;
	
	virtual bool step () = 0;	// update()
	virtual void wait () = 0;

	virtual bool isWindowActive () = 0;

	virtual u32 getTime () = 0;
};

//! Create a video manager
HR_GX_EXP IVideoManager* createVideoManager (core::ISettingsManager* settings = 0);

} // namespace graphics
} // namespace hrengin
#endif//_hrengin_IVideoManager_
