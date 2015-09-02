/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_InputEvent_
#define _awrts_InputEvent_

#include <awrts/common/types.h>
#include <awrts/gui/IGUIElement.h>
#include <awrts/gui/Keycodes.h>

namespace awrts {
namespace gui {

enum class GUIEventType {
	Unknown,
	ElementClosed,
	ElementHovered,
	ElementLeft,
	ElementFocused,
	ElementUnfocused,
};

enum class MouseEventType {
	LButtonDown,
	RButtonDown,
	MButtonDown,
	LButtonUp,
	RButtonUp,
	MButtonUp,
	Wheel,
	Moved,
	LDoubleClick,
	RDoubleClick,
	MDoubleClick,
	LTripleClick,
	RTripleClick,
	MTripleClick
};

enum MouseState {
	MOUSE_LEFT = 0x01,
	MOUSE_RIGHT = 0x02,
	MOUSE_MIDDLE = 0x04
};

enum class InputEventType {
	MouseEvent,
	KeyboardEvent,
	GUIEvent,
	UnknownEvent
};

// Mimics Irrlicht's SEvent
struct InputEvent {
	struct GUIEvent {
		//gui::IGUIElement* caller;
		//gui::IGUIElement* element;
		i32 caller;
		i32 element;
		gui::GUIEventType event;
	};
	struct MouseEvent {
		i32 X;
		i32 Y;
		f32 wheel;
		u8 buttonStates;
		MouseEventType event;
	};
	struct KeyboardEvent {
		KeyCode keyCode;
		wchar_t Char;
		bool pressedDown:1;
		bool shift:1;
		bool control:1;
	};

	InputEventType type;
	union {
		GUIEvent gui;
		MouseEvent mouse;
		KeyboardEvent key;
	};
};

} // namespace gui
} // namespace awrts
#endif //_awrts_InputEvent_
