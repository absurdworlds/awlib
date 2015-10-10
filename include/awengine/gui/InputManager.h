/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_InputManager_
#define _awrts_InputManager_
#include <awengine/common/types.h>
#include <awengine/common/EventListener.h>

#include <awengine/gui/gui.h>
#include <awengine/gui/MouseEvent.h>
#include <awengine/gui/KeyboardEvent.h>

namespace awrts {
namespace gui {
//! Handles user input and generates input events
class InputManager {
public:
	virtual bool registerReceiver(EventListener* receiver) = 0;
	virtual bool unregisterReceiver(EventListener* receiver) = 0;

	#if 0
	virtual void seizeControl(bool seizeCusror, bool seizeKeyboard) = 0;
	#endif
};
} // namespace io
} // namespace awrts
#endif//_awrts_InputManager_
