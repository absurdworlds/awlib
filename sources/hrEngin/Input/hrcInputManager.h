
#ifndef __HG_hrcInputManager__
#define __HG_hrcInputManager__

#include <GUI/Input/hriInputManager.h>

#include <Irrlicht.h>

namespace hrengin
{
namespace gui
{

class hrcInputManager
{
	public:
		virtual irr::gui::ICursorControl* GetCursorControl();
	protected:
		irr::gui::ICursorControl* CursorControl;
};


} // namespace io
} // namespace hrengin

#endif//__HG_hrcInputManager__