/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CInputManager_
#define _hrengin_CInputManager_

#include <forward_list>

#include <Irrlicht/Irrlicht.h>

#include <hrengin/gui/IInputManager.h>

namespace irr {
namespace gui {
class ICursorControl;
}
}

namespace hrengin {
namespace gui {

/*
	Class for handling user input. It inherits from irr::IEventReceiver
	so it can be passed into Irrlicht device as an user event receiver.
	Then it handles events through OnEvent() callback.

	To access user input, use IGUIManager::getInputManager()
 */
class CInputManager : public IInputManager, public irr::IEventReceiver {
public: //IInputManager
	CInputManager(irr::IrrlichtDevice* device);
	virtual bool registerReceiver(IUserInputReceiver* receiver);
	virtual bool unregisterReceiver(IUserInputReceiver* receiver);

public: //irr::IEventReceiver
	virtual bool OnEvent(const irr::SEvent& event);
private:
	irr::gui::ICursorControl* cursor_;
	std::forward_list<IUserInputReceiver*> receivers_;
};


} // namespace io
} // namespace hrengin

#endif//_hrengin_CInputManager_
