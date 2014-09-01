#ifndef _hrengin_IUserInputReceiver_
#define _hrengin_IUserInputReceiver_

#include <hrengin/gui/InputEvent.h>

namespace hrengin {

class IUserInputReceiver {
public:
	virtual bool onUserInput(gui::InputEvent input) = 0;
	virtual bool isEnabled() = 0;
};

} // namespace hrengin


#endif//_hrengin_IControllable_
