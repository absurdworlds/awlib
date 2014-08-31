#ifndef _hrengin_CGUIWindow_
#define _hrengin_CGUIWindow_

#include <hrengin/gui/IGUIWindow.h>

namespace irr {
namespace gui {
class IGUIElement;
}
}

namespace hrengin {
namespace gui {

class CGUIWindow : public IGUIWindow {
public:
	CGUIWindow(irr::gui::IGUIElement* elem);
	virtual ~CGUIWindow();

	virtual u32 getId() const;
	virtual u32 getParentId() const;

	virtual void* getUnderlyingElement() const
	{
		return (void*) irrElement_;
	}

private:
	irr::gui::IGUIElement* irrElement_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIWindow_
