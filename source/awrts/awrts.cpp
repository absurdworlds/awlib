/*
 * Copyright (C) 2013-2014  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/core/Logger.h>
#include <awrts/core/SettingsManager.h>

#include <awrts/graphics/VideoManager.h>
#include <awrts/scene/SceneManager.h>

#include <awrts/physics/PhysicsManager.h>
#include <awrts/physics/PhysicsWorld.h>

#include <awrts/sound/SoundManager.h>

#include <awrts/gui/GUIManager.h>
#include <awrts/gui/InputManager.h>

#include <awrts/game/EventManager.h>
#include <awrts/game/UnitManager.h>
#include <awrts/game/MapManager.h>

#include <awrts/gui/ConsoleGUI.h>

#include "EngineHub.h"

namespace awrts {

void EngineHub::initCore()
{
	settings.reset(core::createSettingsManager());
	settings->addLoader(new core::HDFSettingsLoader());
	settings->loadFile("../data/settings.hdf");

	logger.reset(core::createLogger());
	log = core::FileLog(settings->get("debug.log_path"));
	logger.addLog(&log);
	core::Logger::setGlobalLogger(logger);
}

void EngineHub::initGraphics(EngineHub& hub)
{
	videomgr.reset(graphics::createVideoManager(settings));
	scenemgr.reset(scene::createSceneManager(videomgr));
}

void EngineHub::initPhysics(EngineHub& hub)
{
	phymgr.reset(physics::createPhysicsManager());
	physWorld.reset(phymgr->createPhysicsWorld());
}

void EngineHub::initSound(EngineHub& hub)
{
	soundmgr.reset(sound::createSoundManager());
	sound::SoundLibrary& soundLib = soundmgr->getSoundLibrary();
	soundLib.loadAll(settings->get("data.sound_path"));
}

void EngineHub::initGUI(EngineHub& hub)
{
	guimgr.reset(gui::createGUIManager(*videomgr));
	//"../data/fonts/courier.xml"
	guimgr_->setFont(settings->get("data.font_path"));
	inputmgr.reset(gui::createInputManager(*guimgr));

	console = std::make_unique<gui::ConsoleGUI>(guimgr);
	logger->addLog(console.get());
}

void EngineHub::initGame(EngineHub& hub)
{
	eventmgr = std::make_unique<game::EventManager>();

	unitmgr = std::make_unique<game::UnitManager>(
		       *scenemgr, *phymgr, *eventmgr);
	unitmgr->loadUnitTypes();

	mapmgr = std::make_unique<MapManager>();
	mapmgr->addMapLoader(new game::DefaultMapLoader());
	mapmgr->openMap("../maps/testmap.hdf");

	shell->registerCommand("AddUnit", new addUnit(unitmgr));

	PlayerHuman TestPlayer(scenemgr, unitmgr, pWorld);
	inputmgr->addReceiver(TestPlayer);
}

void initialize()
{
	EngineHub hub;
	hub.initCore();
	hub.initGraphics();
	hub.initPhysics();
	hub.initSound();
	hub.initGUI();
	hub.initGame();
}

void createTestScene(graphics::VideoManager* videomgr, scene::SceneManager* scenemgr)
{
	 scene::Node* lightNode = scenemgr->createNode();
	 graphics::Light* light = videomgr->createLight();
	 lightNode->attachEntity(light);
	 lightNode->setPosition(100.0,1000.0,100.0);
}

int main(int argc, char** argv)
{

}
} // namespace awrts
