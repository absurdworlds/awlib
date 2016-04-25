/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_VideoManager_
#define _aw_VideoManager_

#include <vector>

#include <aw/gui/GUIManager.h>

#include <aw/scene/SceneManager.h>

#include <aw/graphics/VideoManager.h>
#include <aw/graphics/RenderingDevice.h>

#include "VisNode.h"

namespace irr {
class IrrlichtDevice;
namespace video {
class VideoDriver;
}
namespace scene {
class SceneManager;
class AnimatedMesh;
class SceneCollisionManager;
}
} // namespace irr

namespace aw {
namespace gui {
class GUIManager;
}

namespace graphics {
class VideoManager : public VideoManager {
friend class Encore;
friend class GUIManager;
public:
	VideoManager(core::SettingsManager* settings);
	virtual ~VideoManager();
	
	virtual bool step();
	virtual void wait();

	virtual bool isWindowActive();

	virtual RenderingDevice* getRenderingDevice() const;
	virtual scene::SceneManager* getSceneManager() const;
	virtual gui::GUIManager* getGUIManager() const;

	//virtual Mesh* loadMesh(const char * modelname);
	virtual u32 getTime();

private:
	irr::IrrlichtDevice* device_;

	scene::SceneManager* sceneManager_;
	RenderingDevice* renderer_;
	gui::GUIManager* guiManager_;
};

} // namespace graphics
} // namespace aw
#endif//_aw_VideoManager_
