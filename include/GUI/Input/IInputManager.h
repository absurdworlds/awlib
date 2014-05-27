#ifndef __H_INCLUDED__HRENGIN_IInputManager
#define __H_INCLUDED__HRENGIN_IInputManager

#include <Common/hrTypes.h>
#include <Base/Entities/IControllable.h>

#include "hrengin/gui/input/InputEvent.h"

namespace irr
{
namespace gui
{
	class ICursorControl;
}

}

namespace hrengin
{
namespace gui
{
//class IRayPicker;

class IInputManager
{
	public:
		virtual bool RegisterReceiver(IControllable& receiver) = 0;
		virtual bool UnregisterReceiver(IControllable& receiver) = 0;
		//don't see the need in this
		//virtual u32 AddMouseEvent(u32 Event, OnInputCallback callback) = 0;

};

} // namespace io
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IInputManager