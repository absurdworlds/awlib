#ifndef _hrengin_CGUIManager_
#define _hrengin_CGUIManager_

#include <hrengin/gui/IGUIManager.h>

namespace irr {
namespace gui {
	class IGUIEnvironment;
}
}

namespace hrengin {
namespace graphics {
namespace gui {

class CGUIManager : public IGUIManager {
public:
	virtual ~CGUIManager();

	virtual void draw();
private:
	irr::gui::IGUIEnvironment* guienv_;
};

} // namespace gui
} // namespace graphics
} // namespace hrengin

#endif //_hrengin_CGUIManager_
