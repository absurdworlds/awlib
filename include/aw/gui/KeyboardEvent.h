/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_KeyboardEvent_
#define _aw_KeyboardEvent_
#include <aw/common/types.h>
#include <aw/common/Event.h>
#include <aw/gui/Keycodes.h>

namespace aw {
namespace gui {
struct KeyboardEvent : public EventId<KeyboardEvent> {
	KeyCode keyCode;
	u32 Char;
	bool pressedDown:1;
	bool shift:1;
	bool control:1;
};

} // namespace gui
} // namespace aw
#endif //_aw_KeyboardEvent_
