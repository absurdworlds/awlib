/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_MouseEvent_
#define _aw_MouseEvent_
#include <aw/math/Vector2d.h>
#include <aw/common/Event.h>

namespace aw {
namespace gui {
enum MouseState {
	MOUSE_LEFT = 0x01,
	MOUSE_RIGHT = 0x02,
	MOUSE_MIDDLE = 0x04
};

class MouseEvent : public EventId<MouseEvent> {
public:
	enum Action {
		Moved,
		Wheel,
		LButtonDown,
		RButtonDown,
		MButtonDown,
		LButtonUp,
		RButtonUp,
		MButtonUp,
		LDoubleClick,
		RDoubleClick,
		MDoubleClick,
		LTripleClick,
		RTripleClick,
		MTripleClick
	};

	Action action;
	Vector2d<f32> position;
	Vector2d<i32> bounds;
	f32 wheel;
	u8 buttonStates;
};
} // namespace gui
} // namespace aw
#endif //_aw_MouseEvent_
