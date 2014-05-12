
#include "hrcInputManager.h"

#include <Irrlicht/Irrlicht.h>

namespace hrengin
{
namespace gui
{

irr::gui::ICursorControl* hrcInputManager::GetCursorControl()
{
	return CursorControl;
}

u32 hrcInputManager::AddMouseEvent(u32 Button, OnInputCallback callback)
{
	mEvents.push_back(hrInputEvent(Button, callback));
	return mEvents.size()-1;
}

} // namespace io
} // namespace hrengin