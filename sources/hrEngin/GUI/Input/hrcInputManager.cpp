
#include "hrcInputManager.h"

#include <Irrlicht.h>

namespace hrengin
{
namespace gui
{

irr::gui::ICursorControl* hrcInputManager::GetCursorControl()
{
	return CursorControl;
}

} // namespace io
} // namespace hrengin