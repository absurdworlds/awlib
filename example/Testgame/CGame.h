/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_CGame_
#define _awrts_CGame_

#include <awrts/core/ILogger.h>
#include <awrts/core/ISettingsManager.h>
#include <awrts/core/IShell.h>

#include <awrts/graphics/IVideoManager.h>
#include <awrts/graphics/IRenderingDevice.h>
#include <awrts/gui/IGUIManager.h>
#include <awrts/gui/IInputManager.h>
#include <awrts/sound/ISoundManager.h>

#include <awrts/physics/IPhysicsManager.h>
#include <awrts/physics/IPhysicsWorld.h>

#include <awrts/scene/ISceneManager.h>
#include <awrts/game/IEntityManager.h>
#include <awrts/game/IEventManager.h>

namespace awrts {
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
} // namespace awrts
#endif//_awrts_CGame_
