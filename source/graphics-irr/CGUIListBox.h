#ifndef _hrengin_CGUIListBox_
#define _hrengin_CGUIListBox_

#include <hrengin/gui/IGUIListBox.h>

namespace irr {
namespace gui {
class IGUIListBox;
}
}

namespace hrengin {
namespace gui {

class CGUIListBox : public IGUIListBox {
public:
	CGUIListBox(irr::gui::IGUIListBox* elem);
	virtual ~CGUIListBox();
	
	virtual u32 getId() const;
	virtual u32 getParentId() const;
	
	virtual u32 addItem(std::string text);

	virtual std::string getText() const;
	virtual void setText(std::string text);

	virtual void* getUnderlyingElement() const
	{
		return (void*) irrElement_;
	}

private:
	void adjustScrollPosition();

	irr::gui::IGUIListBox* irrElement_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIListBox_
