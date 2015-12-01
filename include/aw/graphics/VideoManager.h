/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_VideoManager_
#define _aw_VideoManager_
#include <aw/common/types.h>

#include <aw/graphics/graphics.h>

namespace aw {
namespace core {
class SettingsManager;
}
namespace gui {
class GUIManager;
}
namespace scene {
class SceneManager;
}
namespace graphics {
class RenderingDevice;

//! Holds other devices and manipuletas the window
class VideoManager {
public:
	virtual ~VideoManager()
	{
	}

	virtual RenderingDevice* getRenderingDevice() const = 0;
	virtual scene::SceneManager* getSceneManager() const = 0;
	virtual gui::GUIManager* getGUIManager() const = 0;

	virtual bool step() = 0;  // update()
	virtual void wait() = 0;

	virtual bool isWindowActive() = 0;

	virtual u32 getTime() = 0;
};

//! Create a video manager
AW_GX_EXP VideoManager* createVideoManager(core::SettingsManager* settings = 0);

} // namespace graphics
} // namespace aw
#endif//_aw_VideoManager_
