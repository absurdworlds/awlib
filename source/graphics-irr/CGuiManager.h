#ifndef _hrengin_CGUIManager_
#define _hrengin_CGUIManager_

#include <hrengin/gui/IGUIManager.h>

namespace irr {
namespace gui {
	class IGUIEnvironment;
}
}

namespace hrengin {
namespace gui {

class CGUIManager : public IGUIManager {
public:
	virtual ~CGUIManager();
private:
	irr::gui::IGUIEnvironment* guienv;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIManager_
