/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/platform/time.h>

#include "CGame.h"

namespace aw {
namespace example {

CGame::CGame ()
	: settings_(core::createSettingsManager()),
	  logger_(core::createLogger())
{
	shell_ = core::createShell(logger_);

	videomgr_ = graphics::createVideoManager(settings_);
	scenemgr_ = videomgr_->getSceneManager();
	renderer_ = videomgr_->getRenderingDevice();

	guimgr_ = videomgr_->getGUIManager();
	inputmgr_ = guimgr_->getInputManager();
	//guimgr_->setFont("../data/fonts/courier.xml");
	
	phymgr_ = physics::createPhysicsManager();
	pWorld_ = phymgr_->createPhysicsWorld();

	drawer_ = phymgr_->createDebugDrawer(renderer_);
	drawer_->setWorld(pWorld_);

	entmgr_  = createEntityManager();
	eventmgr_ = createEventManager();
}

CGame::~CGame ()
{
	delete logger_;
}

bool CGame::frame()
{
	bool runEngine = true;
	bool debugMode = false;
	
	runEngine = videomgr_->step();
	if(!runEngine) {
		return false;
	}

	if(videomgr_->isWindowActive()) {
		renderer_->beginRender();
		scenemgr_->drawScene();
		settings_->getValue("debugmode", debugMode);
		if(debugMode) {
			renderer_->drawDebug();
			drawer_->render();
		}
		guimgr_->draw();
		eventmgr_->advance();
		//runEngine = pWorld_->step();
		renderer_->endRender();
	} else {
		videomgr_->wait();
	}

	return true;
}

bool CGame::run ()
{
	bool runEngine = true;

	aw::u32 curTime = hrengin::getTime();
	aw::u32 lastTime;
	
	// Here I show how I implement my game loop.
	do {
		lastTime = curTime;
		curTime = aw::getTime();
		runEngine = frame();
	}
	while(runEngine);

	return runEngine;
}

void CGame::loadSettings ()
{
	settings_->setValue("debugmode",false);

	settings_->loadSettings();
}
} // namespace example
} // namespace aw
