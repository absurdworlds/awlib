/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_UserInputReceiver_
#define _awrts_UserInputReceiver_

#include <awrts/gui/InputEvent.h>

namespace awrts {

class UserInputReceiver {
public:
	virtual bool onUserInput(gui::InputEvent input) = 0;
	virtual bool isEnabled() = 0;
};

} // namespace awrts
#endif//_awrts_UserInputReceiver_
