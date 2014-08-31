#ifndef _hrengin_IGUIManager_
#define _hrengin_IGUIManager_

#include <hrengin/common/Rect.h>

namespace hrengin {
namespace io {
class IInputManager;
}
namespace gui {
class IGUIElement;
class IGUIWindow;

class IGUIManager {
public:
	virtual ~IGUIManager() {};

	virtual void draw() = 0;

	virtual io::IInputManager* getInputManager() = 0;

	virtual IGUIWindow* addWindow(Rect<i32> rect, bool isModal = false, 
		const wchar_t* title = 0, IGUIElement* parent = 0,
		i32 id = -1) = 0;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIManager_
