#ifndef _hrengin_CGUIManager_
#define _hrengin_CGUIManager_

#include <hrengin/gui/IGUIManager.h>

namespace irr {
class IrrlichtDevice;
namespace gui {
class IGUIEnvironment;
}
}

namespace hrengin {
namespace gui {

class CGUIManager : public IGUIManager {
public:
	CGUIManager(irr::gui::IGUIEnvironment* guienv,
	irr::IrrlichtDevice* device);
	virtual ~CGUIManager();

	virtual void draw();

	virtual io::IInputManager* getInputManager();
private:
	irr::IrrlichtDevice* device_;
	irr::gui::IGUIEnvironment* guienv_;
	io::IInputManager* inputmgr_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIManager_
