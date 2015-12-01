/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <Irrlicht/IrrlichtDevice.h>

#include <aw/common/EventListener.h>

#include <aw/irr/gui/InputManager.h>

namespace aw {
namespace gui {
namespace impl {
bool InputManager::convertEvent(const irr::SEvent& irrEvent, Event*& event) {
	switch(irrEvent.EventType) {
	case irr::EET_MOUSE_INPUT_EVENT: {
		auto mevent = new MouseEvent();
		auto screen = device->getVideoDriver()->getScreenSize();
		mevent->position = Vector2d<f32>(f32(irrEvent.MouseInput.X) / screen.Width,
		                                 f32(irrEvent.MouseInput.Y) / screen.Height);
		mevent->bounds = Vector2d<i32>(screen.Width, screen.Height);
		mevent->wheel = irrEvent.MouseInput.Wheel;
		mevent->buttonStates = irrEvent.MouseInput.ButtonStates;

		switch(irrEvent.MouseInput.Event) {
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			mevent->action = MouseEvent::LButtonDown;
			break;
		case irr::EMIE_RMOUSE_PRESSED_DOWN:
			mevent->action = MouseEvent::RButtonDown;
			break;
		case irr::EMIE_MMOUSE_PRESSED_DOWN:
			mevent->action = MouseEvent::MButtonDown;
			break;
		case irr::EMIE_LMOUSE_LEFT_UP:
			mevent->action = MouseEvent::LButtonUp;
			break;
		case irr::EMIE_RMOUSE_LEFT_UP:
			mevent->action = MouseEvent::RButtonUp;
			break;
		case irr::EMIE_MMOUSE_LEFT_UP:
			mevent->action = MouseEvent::MButtonUp;
			break;
		case irr::EMIE_LMOUSE_DOUBLE_CLICK:
			mevent->action = MouseEvent::LDoubleClick;
			break;
		case irr::EMIE_RMOUSE_DOUBLE_CLICK:
			mevent->action = MouseEvent::RDoubleClick;
			break;
		case irr::EMIE_MMOUSE_DOUBLE_CLICK:
			mevent->action = MouseEvent::MDoubleClick;
			break;
		case irr::EMIE_LMOUSE_TRIPLE_CLICK:
			mevent->action = MouseEvent::LTripleClick;
			break;
		case irr::EMIE_RMOUSE_TRIPLE_CLICK:
			mevent->action = MouseEvent::RTripleClick;
			break;
		case irr::EMIE_MMOUSE_TRIPLE_CLICK:
			mevent->action = MouseEvent::MTripleClick;
			break;
		case irr::EMIE_MOUSE_MOVED:
			mevent->action = MouseEvent::Moved;
			break;
		case irr::EMIE_MOUSE_WHEEL:
			mevent->action = MouseEvent::Wheel;
			break;
		}
		event = mevent;
		return true;
	}
	case irr::EET_KEY_INPUT_EVENT:
#if 0 // Ignore keyboard event - I don't really need it while testing
		hrgEvent.type = InputEventType::KeyboardEvent;
		hrgEvent.key.Char = irrEvent.KeyInput.Char;
		hrgEvent.key.keyCode = KeyCode(irrEvent.KeyInput.Key);
		hrgEvent.key.pressedDown = irrEvent.KeyInput.PressedDown;
		hrgEvent.key.control = irrEvent.KeyInput.Control;
		hrgEvent.key.shift = irrEvent.KeyInput.Shift;
		return true;
#endif
	default:
		return false;
	}
}

InputManager::InputManager(irr::IrrlichtDevice* device)
	: device(device)
{
	device->setEventReceiver(this);
	cursor_ = device->getCursorControl();
}

bool InputManager::OnEvent(const irr::SEvent& event)
{
	Event* hrEvent; 
	bool convert = convertEvent(event, hrEvent);

	if(!convert)
		return false;

	for(auto listener : receivers_) {
		listener->onEvent(hrEvent);
	}

	// return false, so Irrlicht processes other events
	return false;
}

bool InputManager::registerReceiver(EventListener* receiver)
{
	receivers_.push_front(receiver);
	return true;
}

bool InputManager::unregisterReceiver(EventListener* receiver)
{
	//remove from mReceivers

	return true;
}
} // namespace impl
} // namespace io
} // namespace aw
