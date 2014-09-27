/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Irrlicht/IrrlichtDevice.h>

#include <hrengin/gui/IUserInputReceiver.h>

#include "CVideoManager.h"

#include "CInputManager.h"


namespace hrengin {
namespace gui {


CInputManager::CInputManager(core::ISettingsManager* settings)
{
	i32 wndHandle;
	settings->getValue("platform.win32.wndHandle", wndHandle);

	OIS::ParamList pl;

	pl.insert(std::make_pair(std::string("WINDOW"), std::to_string( u32(wndHandle) )));

	inputMgr_ = OIS::InputManager::createInputSystem( pl );

	keyboard_ = static_cast<OIS::Keyboard*>(inputMgr_->createInputObject( OIS::OISKeyboard, true ));
	cursor_ = static_cast<OIS::Mouse*>(inputMgr_->createInputObject( OIS::OISMouse, true ));

	cursor_->setEventCallback(this);
	keyboard_->setEventCallback(this);

	genKeyMap();
}

InputEvent CInputManager::key(OIS::KeyEvent const& arg)
{
	InputEvent event;
	event.type = InputEventType::KeyboardEvent;

	
	event.key.control = keyboard_->isModifierDown(OIS::Keyboard::Ctrl);
	event.key.shift = keyboard_->isModifierDown(OIS::Keyboard::Shift);
	
	event.key.keyCode = keyMap_[arg.key];

	return event;
}

bool CInputManager::keyPressed( OIS::KeyEvent const& arg )
{
	InputEvent event = key(arg);

	event.key.pressedDown = true;

	return true;
}

bool CInputManager::keyReleased( OIS::KeyEvent const& arg )
{
	InputEvent event = key(arg);

	event.key.pressedDown = false;

	return true;
}


InputEvent CInputManager::mouse(OIS::MouseEvent const& arg)
{
	OIS::MouseState const& mstate = cursor_->getMouseState();

	InputEvent event;

	event.type = InputEventType::MouseEvent;

	event.mouse.X = mstate.X.abs;
	event.mouse.Y = mstate.Y.abs;
	event.mouse.wheel = mstate.Z.rel;
	event.mouse.buttonStates = mstate.buttonDown(OIS::MB_Left) ? MOUSE_LEFT : 0 +
		mstate.buttonDown(OIS::MB_Right) ? MOUSE_RIGHT : 0 + 
		mstate.buttonDown(OIS::MB_Middle) ? MOUSE_MIDDLE : 0;

	return event;
}

bool CInputManager::mouseMoved( OIS::MouseEvent const& arg )
{
	InputEvent event = mouse(arg);
	
	if(!math::equals(event.mouse.wheel,0.0f)) {
		event.mouse.event = MouseEventType::Wheel;
	} else {
		event.mouse.event = MouseEventType::Moved;
	}
	return true;
}

bool CInputManager::mousePressed( OIS::MouseEvent const& arg, OIS::MouseButtonID id )
{
	InputEvent event = mouse(arg);
	switch(id) {
	case OIS::MB_Right:
		event.mouse.event = MouseEventType::LButtonDown;
		break;
	case OIS::MB_Left:
		event.mouse.event = MouseEventType::RButtonDown;
		break;
	case OIS::MB_Middle:
		event.mouse.event = MouseEventType::MButtonDown;
		break;
	}
}
bool CInputManager::mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id )
{
	InputEvent event = mouse(arg);
	switch(id) {
	case OIS::MB_Right:
		event.mouse.event = MouseEventType::LButtonUp;
		break;
	case OIS::MB_Left:
		event.mouse.event = MouseEventType::RButtonUp;
		break;
	case OIS::MB_Middle:
		event.mouse.event = MouseEventType::MButtonUp;
		break;
	}
}

void CInputManager::broadcast(InputEvent event)
{
	if(event.type == InputEventType::UnknownEvent) {
		return;
	}

	for(std::forward_list<IUserInputReceiver*>::iterator it = receivers_.begin(); it != receivers_.end(); ++it) {
		if((*it)->isEnabled()) {
			(*it)->onUserInput(event);
		}
	}
}

bool CInputManager::registerReceiver(IUserInputReceiver* receiver)
{
	receivers_.push_front(receiver);
	return true;
}

bool CInputManager::unregisterReceiver(IUserInputReceiver* receiver)
{
	//remove from mReceivers
	
	return true;
}

} // namespace io
} // namespace hrengin
