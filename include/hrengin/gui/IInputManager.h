#ifndef _hrengin_IInputManager_
#define _hrengin_IInputManager_

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/hrenginapi.h>
#include <hrengin/entities/IControllable.h>

#include <hrengin/gui/InputEvent.h>

namespace irr {
namespace gui {
	class ICursorControl;
}

}

namespace hrengin {
namespace gui {
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

#endif//__H_INCLUDED__HRENGIN_IInputManager