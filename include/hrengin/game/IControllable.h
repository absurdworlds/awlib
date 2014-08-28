#ifndef _hrengin_IControllable_
#define _hrengin_IControllable_

#include "hrengin/gui/InputEvent.h"

namespace hrengin {

class IControllable
{
public:
	virtual bool ReceiveInput(gui::InputEvent input) = 0;
	virtual bool IsEnabled() = 0;
};

} // namespace hrengin


#endif//_hrengin_IControllable_
