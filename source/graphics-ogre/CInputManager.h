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

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <hrengin/core/ISettingsManager.h>

#include <hrengin/gui/IInputManager.h>

namespace hrengin {
namespace gui {

/*
	Class for handling user input. It inherits from irr::IEventReceiver
	so it can be passed into Irrlicht device as an user event receiver.
	Then it handles events through OnEvent() callback.

	To access user input, use IGUIManager::getInputManager()
 */
class CInputManager : public IInputManager, public OIS::KeyListener, public OIS::MouseListener {
public: //IInputManager
	CInputManager(core::ISettingsManager* settings);
	virtual bool registerReceiver(IUserInputReceiver* receiver);
	virtual bool unregisterReceiver(IUserInputReceiver* receiver);

	// OIS::KeyListener
	virtual bool keyPressed( OIS::KeyEvent const& arg );
	virtual bool keyReleased( OIS::KeyEvent const& arg );
	// OIS::MouseListener
	virtual bool mouseMoved( OIS::MouseEvent const& arg );
	virtual bool mousePressed(  OIS::MouseEvent const& arg, OIS::MouseButtonID id );
	virtual bool mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id );

	virtual void broadcast(InputEvent event);
private:
	OIS::InputManager* inputMgr_;
	OIS::Mouse*    cursor_;
	OIS::Keyboard* keyboard_;
	std::forward_list<IUserInputReceiver*> receivers_;
};


} // namespace io
} // namespace hrengin

#endif//_hrengin_CInputManager_
