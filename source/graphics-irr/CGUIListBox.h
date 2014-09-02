#ifndef _hrengin_CGUIListBox_
#define _hrengin_CGUIListBox_

#include <hrengin/gui/IGUIListBox.h>

namespace irr {
namespace gui {
class IGUIElement;
}
}

namespace hrengin {
namespace gui {

class CGUIListBox : public IGUIListBox {
public:
	CGUIListBox(irr::gui::IGUIElement* elem);
	virtual ~CGUIListBox();
	
	virtual u32 getId() const;
	virtual u32 getParentId() const;
	
	virtual std::string getText() const;

	virtual void* getUnderlyingElement() const
	{
		return (void*) irrElement_;
	}

private:
	irr::gui::IGUIElement* irrElement_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIListBox_
