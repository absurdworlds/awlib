/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_InputManager_
#define _hrengin_InputManager_

#include <forward_list>

#include <Irrlicht/irrlicht.h>

#include <hrengin/gui/InputManager.h>

namespace irr {
namespace gui {
class CursorControl;
}
}

namespace hrengin {
namespace gui {

/*
 * Class for handling user input. It inherits from irr::IEventReceiver
 * so it can be passed into Irrlicht device as an user event receiver.
 * Then it handles events through OnEvent() callback.
 *
 * To access user input, use GUIManager::getInputManager()
 */
class InputManager : public InputManager, public irr::IEventReceiver {
public: //InputManager
	InputManager(irr::IrrlichtDevice* device);
	virtual bool registerReceiver(UserInputReceiver* receiver);
	virtual bool unregisterReceiver(UserInputReceiver* receiver);

public: //irr::IEventReceiver
	virtual bool OnEvent(const irr::SEvent& event);
private:
	irr::gui::ICursorControl* cursor_;
	std::forward_list<UserInputReceiver*> receivers_;
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_InputManager_
