/**
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

void convertEvent(const irr::SEvent& irrEvent, InputEvent& hrgEvent) {
	switch(irrEvent.EventType) {
	case irr::EET_MOUSE_INPUT_EVENT:
		hrgEvent.type = InputEventType::MouseEvent;
		hrgEvent.mouse.X = irrEvent.MouseInput.X;
		hrgEvent.mouse.Y = irrEvent.MouseInput.Y;
		hrgEvent.mouse.wheel = irrEvent.MouseInput.Wheel;
		hrgEvent.mouse.buttonStates = irrEvent.MouseInput.ButtonStates;

		switch(irrEvent.MouseInput.Event) {
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			hrgEvent.mouse.event = MouseEventType::LButtonDown;
			break;
		case irr::EMIE_RMOUSE_PRESSED_DOWN:
			hrgEvent.mouse.event = MouseEventType::RButtonDown;
			break;
		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			hrgEvent.mouse.event = MouseEventType::MButtonDown;
			break;
		case irr::EMIE_LMOUSE_LEFT_UP:
			hrgEvent.mouse.event = MouseEventType::LButtonUp;
			break;
		case irr::EMIE_RMOUSE_LEFT_UP:
			hrgEvent.mouse.event = MouseEventType::RButtonUp;
			break;
		case irr::EMIE_MMOUSE_LEFT_UP:
			hrgEvent.mouse.event = MouseEventType::MButtonUp;
			break;
		case irr::EMIE_LMOUSE_DOUBLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::LDoubleClick;
			break;
		case irr::EMIE_RMOUSE_DOUBLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::RDoubleClick;
			break;
		case irr::EMIE_MMOUSE_DOUBLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::MDoubleClick;
			break;
		case irr::EMIE_LMOUSE_TRIPLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::LTripleClick;
			break;
		case irr::EMIE_RMOUSE_TRIPLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::RTripleClick;
			break;
		case irr::EMIE_MMOUSE_TRIPLE_CLICK:
			hrgEvent.mouse.event = MouseEventType::MTripleClick;
			break;
		case irr::EMIE_MOUSE_MOVED:
			hrgEvent.mouse.event = MouseEventType::Moved;
			break;
		case irr::EMIE_MOUSE_WHEEL:
			hrgEvent.mouse.event = MouseEventType::Wheel;
			break;
		}
		break;
	case irr::EET_KEY_INPUT_EVENT:
		hrgEvent.type = InputEventType::KeyboardEvent;
		hrgEvent.key.Char = irrEvent.KeyInput.Char;
		hrgEvent.key.keyCode = irrEvent.KeyInput.Key;
		hrgEvent.key.pressedDown = irrEvent.KeyInput.PressedDown;
		hrgEvent.key.control = irrEvent.KeyInput.Control;
		hrgEvent.key.shift = irrEvent.KeyInput.Shift;
		break;
	case irr::EET_GUI_EVENT:
		hrgEvent.type = InputEventType::GUIEvent;
		if(irrEvent.GUIEvent.Caller) {
			hrgEvent.gui.caller = irrEvent.GUIEvent.Caller->getID();
		} else {
			hrgEvent.gui.caller = 0;
		}
		if(irrEvent.GUIEvent.Element) {
			hrgEvent.gui.element = irrEvent.GUIEvent.Element->getID();
		} else {
			hrgEvent.gui.element = 0;
		}
		switch(irrEvent.GUIEvent.EventType) {
		case irr::gui::EGET_ELEMENT_CLOSED:
			hrgEvent.gui.event = gui::GUIEventType::ElementClosed;
			break;
		case irr::gui::EGET_ELEMENT_HOVERED:
			hrgEvent.gui.event = gui::GUIEventType::ElementHovered;
			break;
		case irr::gui::EGET_ELEMENT_LEFT:
			hrgEvent.gui.event = gui::GUIEventType::ElementLeft;
			break;
		case irr::gui::EGET_ELEMENT_FOCUSED:
			hrgEvent.gui.event = gui::GUIEventType::ElementFocused;
			break;
		case irr::gui::EGET_ELEMENT_FOCUS_LOST:
			hrgEvent.gui.event = gui::GUIEventType::ElementUnfocused;
			break;
		default:
			hrgEvent.gui.event = gui::GUIEventType::Unknown;
		}
		break;
	default:
		hrgEvent.type = InputEventType::UnknownEvent;
	}
}

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
}


bool CInputManager::keyPressed( OIS::KeyEvent const& arg )
{
	InputEvent hrEvent;

	hrEvent.type = InputEventType::KeyboardEvent;
	hrEvent.key.pressedDown = true;
	
	hrEvent.key.control = keyboard_->isModifierDown(OIS::Keyboard::Ctrl);
	hrEvent.key.shift = keyboard_->isModifierDown(OIS::Keyboard::Shift);

	switch (arg.key) {

	default:
		break;
	}
}

bool CInputManager::keyReleased( OIS::KeyEvent const& arg )
{
	InputEvent hrEvent;

	hrEvent.type = InputEventType::KeyboardEvent;
	hrEvent.key.pressedDown = false;
	
	hrEvent.key.control = keyboard_->isModifierDown(OIS::Keyboard::Ctrl);
	hrEvent.key.shift = keyboard_->isModifierDown(OIS::Keyboard::Shift);

	switch (arg.key) {

	default:
		break;
	}
}

bool CInputManager::mouseMoved( OIS::MouseEvent const& arg )
{
	InputEvent hrEvent;

	hrEvent.type = InputEventType::MouseEvent;

	OIS::MouseState const& mstate = cursor_->getMouseState();
	hrEvent.mouse.X = mstate.X.abs;
	hrEvent.mouse.Y = mstate.Y.abs;
	hrEvent.mouse.buttonStates = mstate.buttonDown(OIS::MB_Left) ? MOUSE_LEFT : 0 +
		mstate.buttonDown(OIS::MB_Right) ? MOUSE_RIGHT : 0 + 
		mstate.buttonDown(OIS::MB_Middle) ? MOUSE_MIDDLE : 0;
	hrEvent.mouse.event = MouseEventType::Moved;

}
bool CInputManager::mousePressed( OIS::MouseEvent const& arg, OIS::MouseButtonID id )
{

}
bool CInputManager::mouseReleased(OIS::MouseEvent const& arg, OIS::MouseButtonID id )
{

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
