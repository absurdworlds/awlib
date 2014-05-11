
#ifndef __HG_hriInputManager__
#define __HG_hriInputManager__

#include <Base/hrTypes.h>

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

typedef void (*OnInputCallback)(u32 Event);
//class hriRayPicker;

class hriInputManager
{
	public:
		virtual u32 AddMouseEvent(u32 Button, OnInputCallback callback) = 0;

};

} // namespace io
} // namespace hrengin

#endif//__HG_hriInputManager__