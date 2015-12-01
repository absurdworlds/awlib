/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_InputManager_
#define _aw_InputManager_
#include <aw/common/types.h>
#include <aw/common/EventListener.h>

#include <aw/gui/gui.h>
#include <aw/gui/MouseEvent.h>
#include <aw/gui/KeyboardEvent.h>

namespace aw {
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
} // namespace aw
#endif//_aw_InputManager_
