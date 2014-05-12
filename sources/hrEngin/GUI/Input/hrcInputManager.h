
#ifndef __HG_hrcInputManager__
#define __HG_hrcInputManager__

#include <vector>

#include <Irrlicht/Irrlicht.h>

#include <GUI/Input/hriInputManager.h>

namespace hrengin
{
namespace gui
{

class hrcInputManager
{
	public:
		u32 AddMouseEvent(u32 Button, OnInputCallback callback);
	public:
		virtual irr::gui::ICursorControl* GetCursorControl();
	protected:
		irr::gui::ICursorControl* CursorControl;
		std::vector<hrInputEvent> mEvents;
};


} // namespace io
} // namespace hrengin

#endif//__HG_hrcInputManager__