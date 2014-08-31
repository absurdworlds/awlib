#ifndef _hrengin_IInputManager_
#define _hrengin_IInputManager_

#include <hrengin/common/types.h>
#include <hrengin/common/api.h>
#include <hrengin/game/IControllable.h>

#include <hrengin/gui/InputEvent.h>

namespace irr {
namespace gui {
	class ICursorControl;
}
}

namespace hrengin {
namespace io {
//class IRayPicker;

class IInputManager
{
	public:
		virtual bool RegisterReceiver(IControllable& receiver) = 0;
		virtual bool UnregisterReceiver(IControllable& receiver) = 0;
		//don't see the need in this
		//virtual u32 AddMouseEvent(u32 Event, OnInputCallback callback) = 0;

};

HRENGINGRAPHICS_API IInputManager& getInputManager();

} // namespace io
} // namespace hrengin

#endif//_hrengin_IInputManager_
