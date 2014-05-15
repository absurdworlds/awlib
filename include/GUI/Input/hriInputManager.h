
#ifndef __HG_hriInputManager__
#define __HG_hriInputManager__

#include <Base/hrTypes.h>
#include <Base/Entities/hriInputReceiver.h>

#include "hrInputEvent.h"

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
//class hriRayPicker;

class hriInputManager
{
	public:
		virtual bool RegisterReceiver(IControllable& receiver) = 0;
		virtual bool UnregisterReceiver(IControllable& receiver) = 0;
		//don't see the need in this
		//virtual u32 AddMouseEvent(u32 Event, OnInputCallback callback) = 0;

};

} // namespace io
} // namespace hrengin

#endif//__HG_hriInputManager__