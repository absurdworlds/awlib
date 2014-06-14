#ifndef __H_INCLUDED__HRENGIN_IControllable
#define __H_INCLUDED__HRENGIN_IControllable

#include "hrengin/gui/input/InputEvent.h"

namespace hrengin
{

class IControllable
{
public:
	virtual bool ReceiveInput(gui::InputEvent input) = 0;
	virtual bool IsEnabled() = 0;
};

} // namespace hrengin


#endif//__H_INCLUDED__HRENGIN_IControllable