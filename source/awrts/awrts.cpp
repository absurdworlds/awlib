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
void initialize()
{
	std::unique_ptr<core::Logger> logger = core::createLogger(&logbuffer);
	std::unique_ptr<core::Settings> settings = core::createSettingsManager();
	FileLog log(settings->get("debug.log_path"));
	logger.addLog(log);

	core::Logger::setGlobalLogger(logger);


	settings->addLoader(new core::HDFSettingsLoader());
	settings->loadFile("../data/settings.hdf");

	std::unique_ptr<graphics::VideoManager> videomgr(graphics::createVideoManager(settings));
	std::unique_ptr<scene::SceneManager> scenemgr(scene::createSceneManager(videomgr));

	std::unique_ptr<physics::PhysicsManager> phymgr(physics::createPhysicsManager());
	std::unique_ptr<physics::World> pWorld(phymgr->createPhysicsWorld());

	std::unique_ptr<sound::SoundManager> soundmgr(sound::createSoundManager());
	sound::SoundLibrary& soundLib = soundmgr->getSoundLibrary();
	soundLib.loadAll();


	std::unique_ptr<gui::GUIManager> guimgr(gui::createGUIManager(videomgr));
	guimgr_->setFont("../data/fonts/courier.xml");

	std::unique_ptr<platform::InputManager> inputmgr(platform::createInputManager());

	std::unique_ptr<ConsoleGUI> console(new ConsoleGUI(guimgr));
	logger->addLog(console);

	std::unique_ptr<game::EventManager> eventmgr(new game::EventManager());

	std::unique_ptr<game::UnitManager> unitmgr(new game::UnitManager(scenemgr, phymgr, eventmgr));
	unitmgr->loadUnitTypes();

	std::unique_ptr<game::MapManager> mapmgr(game::createMapManager());
	mapmgr->addMapLoader(new game::DefaultMapLoader());
	mapmgr->openMap("../maps/testmap.hdf");

	Shell shell;
	shell->registerCommand("AddUnit", new addUnit(unitmgr));

	PlayerHuman TestPlayer(scenemgr, unitmgr, pWorld);
	inputmgr->addReceiver(TestPlayer);
}

void createTestScene(graphics::VideoManager* videomgr, scene::SceneManager* scenemgr)
{
	 scene::Node* lightNode = scenemgr->createNode();
	 graphics::Light* light = videomgr->createLight();
	 lightNode->attachEntity(light);
	 lightNode->setPosition(100.0,1000.0,100.0);
}
} // namespace awrts
