/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_KeyboardEvent_
#define _awrts_KeyboardEvent_
#include <awengine/common/types.h>
#include <awengine/common/types.h>
#include <awengine/gui/Keycodes.h>

namespace awrts {
namespace gui {
struct KeyboardEvent : EventId<KeyboardEvent> {
private:
	KeyCode keyCode;
	u32 Char;
	bool pressedDown:1;
	bool shift:1;
	bool control:1;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_KeyboardEvent_
