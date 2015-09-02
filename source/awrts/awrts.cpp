/*
 * Copyright (C) 2013-2014  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
namespace awrts {

struct EngineHub {
	std::unique_ptr<core::Logger> logger;
	std::unique_ptr<core::Settings> settings;
	core::FileLog log;

	std::unique_ptr<graphics::VideoManager> videomgr;
	std::unique_ptr<scene::SceneManager> scenemgr;

	std::unique_ptr<physics::PhysicsManager> phymgr;
	std::unique_ptr<physics::World> physWorld;

	std::unique_ptr<sound::SoundManager> soundmgr;
	std::unique_ptr<gui::GUIManager> guimgr;
	std::unique_ptr<gui::InputManager> inputmgr;
	std::unique_ptr<ConsoleGUI> console;

	std::unique_ptr<game::EventManager> eventmgr;
	std::unique_ptr<game::UnitManager> unitmgr;
	std::unique_ptr<game::MapManager> mapmgr;

	Shell shell;
};

void initCore(EngineHub& hub)
{
	hub.settings = core::createSettingsManager();
	settings->addLoader(new core::HDFSettingsLoader());
	settings->loadFile("../data/settings.hdf");

	hub.logger = core::createLogger();
	hub.log = core::FileLog(settings->get("debug.log_path"));
	logger.addLog(log);
	core::Logger::setGlobalLogger(logger);
}

void initGraphics(EngineHub& hub)
{
	hub.videomgr = graphics::createVideoManager(hub.settings);
	hub.scenemgr = scene::createSceneManager(hub.videomgr);
}

void initPhysics(EngineHub& hub)
{
	hub.phymgr = physics::createPhysicsManager();
	hub.physWorld = phymgr->createPhysicsWorld();
}

void initSound(EngineHub& hub)
{
	hub.soundmgr = sound::createSoundManager();
	sound::SoundLibrary& soundLib = soundmgr->getSoundLibrary();
	soundLib.loadAll(hub.settings->get("data.sound_path"));
}

void initGUI(EngineHub& hub)
{
	hub.guimgr = gui::createGUIManager(hub.videomgr);
	//"../data/fonts/courier.xml"
	guimgr_->setFont(hub.settings->get("data.font_path"));
	hub.inputmgr = gui::createInputManager(hub.guimgr);

	hub.console = new ConsoleGUI(guimgr);
	hub.logger->addLog(*console);
}

void initGame(EngineHub& hub)
{
	hub.eventmgr = new game::EventManager();

	hub.unitmgr = new game::UnitManager(*hub.scenemgr, *hub.phymgr, *hub.eventmgr);
	unitmgr->loadUnitTypes();

	hub.mapmgr = game::createMapManager();
	hub.mapmgr->addMapLoader(new game::DefaultMapLoader());
	hub.mapmgr->openMap("../maps/testmap.hdf");

	shell->registerCommand("AddUnit", new addUnit(unitmgr));

	PlayerHuman TestPlayer(scenemgr, unitmgr, pWorld);
	inputmgr->addReceiver(TestPlayer);
}

void initialize()
{
	EngineHub hub;
}

void createTestScene(graphics::VideoManager* videomgr, scene::SceneManager* scenemgr)
{
	 scene::Node* lightNode = scenemgr->createNode();
	 graphics::Light* light = videomgr->createLight();
	 lightNode->attachEntity(light);
	 lightNode->setPosition(100.0,1000.0,100.0);
}

int main(int argc, char*[] argv)
{

}
} // namespace awrts
