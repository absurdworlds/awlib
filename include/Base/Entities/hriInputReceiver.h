
#ifndef __HR_INPUTRECEIVER__
#define __HR_INPUTRECEIVER__

#include "GUI/Input/hrInputEvent.h"


namespace hrengin
{

class hriInputReceiver
{
public:
	virtual bool ReceiveInput(gui::hrInputEvent input) = 0;
	virtual bool IsEnabled() = 0;
};

} // namespace hrengin


#endif//__HR_INPUTRECEIVER__