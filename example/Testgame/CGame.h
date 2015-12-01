/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CGame_
#define _aw_CGame_

#include <aw/core/ILogger.h>
#include <aw/core/ISettingsManager.h>
#include <aw/core/IShell.h>

#include <aw/graphics/IVideoManager.h>
#include <aw/graphics/IRenderingDevice.h>
#include <aw/gui/IGUIManager.h>
#include <aw/gui/IInputManager.h>
#include <aw/sound/ISoundManager.h>

#include <aw/physics/IPhysicsManager.h>
#include <aw/physics/IPhysicsWorld.h>

#include <aw/scene/ISceneManager.h>
#include <aw/game/IEntityManager.h>
#include <aw/game/IEventManager.h>

namespace aw {
namespace example {

class CGame {
public:
	CGame ();
	virtual ~CGame ();
	
	void loadSettings ();
	bool run ();
	bool frame ();

	graphics::IVideoManager* getVideoManager()
	{
		return videomgr_;
	}

	graphics::IRenderingDevice* getRenderer()
	{
		return renderer_;
	}

	gui::IGUIManager* getGUIManager()
	{
		return guimgr_;
	}

	scene::ISceneManager* getSceneManager()
	{
		return scenemgr_;
	}

	physics::IPhysicsManager* getPhysicsManager()
	{
		return phymgr_;
	}
private:
	// core 
	core::ILogger* logger_;
	core::ISettingsManager* settings_;
	core::IShell* shell_;

	// grap/home/hudd/Clipps/hics
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
} // namespace aw
#endif//_aw_CGame_
