#ifndef _hrengin_IGUIManager_
#define _hrengin_IGUIManager_

namespace hrengin {
namespace io {
class IInputManager;
}
namespace graphics {
namespace gui {


class IGUIManager {
public:
	virtual ~IGUIManager() {};

	virtual void draw() = 0;

	virtual io::IInputManager* getInputManager() = 0;
};

} // namespace gui
} // namespace graphics
} // namespace hrengin

#endif //_hrengin_IGUIManager_
