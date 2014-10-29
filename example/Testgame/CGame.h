/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CGame_
#define _hrengin_CGame_

#include <hrengin/core/ILogger.h>
#include <hrengin/core/ISettingsManager.h>
#include <hrengin/core/IShell.h>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/graphics/IRenderingDevice.h>
#include <hrengin/gui/IGUIManager.h>
#include <hrengin/gui/IInputManager.h>
#include <hrengin/sound/ISoundManager.h>

#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/physics/IPhysicsWorld.h>

#include <hrengin/scene/ISceneManager.h>
#include <hrengin/game/IEntityManager.h>
#include <hrengin/game/IEventManager.h>

namespace hrengin {
namespace example {

class CGame {
public:
	CGame ();
	virtual ~CGame ();
	
	void loadSettings ();
	bool run ();

	graphics::IRenderingDevice* getRenderer()
	{
		return renderer_;
	}
private:
	// core 
	core::ILogger* logger_;
	core::ISettingsManager* settings_;
	core::IShell* shell_;

	// graphics
	graphics::IVideoManager* videomgr_;
	graphics::IRenderingDevice* renderer_;

	// gui
	gui::IGUIManager* guimgr_;
	gui::IInputManager* inputmgr_;

	// physics
	physics::IPhysicsManager* phymgr_;
	physics::IPhysicsWorld*   pWorld_;
	
	physics::IDebugDrawer*    drawer_;

	// game
	scene::ISceneManager* scenemgr_;

	IEntityManager* entmgr_;
	IEventManager* eventmgr_;
};

} // namespace example
} // namespace hrengin
#endif//_hrengin_CGame_
