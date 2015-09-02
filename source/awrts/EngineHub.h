/*
 * Copyright (C) 2013-2014  absurdworlds
 * Copyright (C)      2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_EngineHub_
#define _awrts_EngineHub_
#include <memory>

namespace awrts {
namespace core {
class Logger
class SettingsManager
}
namespace graphics {
class VideoManager
}
namespace scene {
class SceneManager
}
namespace physics {
class PhysicsManager
class PhysicsWorld
}
namespace sound {
class SoundManager
}
namespace gui {
class GUIManager
class InputManager
class ConsoleGUI
}
namespace game {
class EventManager
class UnitManager
class MapManager
}

struct EngineHub {
	std::unique_ptr<core::Logger> logger;
	std::unique_ptr<core::SettingsManager> settings;
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

	void initCore();
	void initGraphics();
	void initPhysics();
	void initSound();
	void initGUI();
	void initGame();
};
} // namespace awrts
#endif//_awrts_EngineHub_
