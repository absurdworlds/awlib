/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
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
	CGUIListBox();
	virtual ~CGUIListBox();
	
	virtual u32 getId() const;
	virtual u32 getParentId() const;
	
	virtual u32 addItem(std::string text);

	virtual std::string getText() const;
	virtual void setText(std::string text);

	virtual void* getUnderlyingElement() const
	{
		return (void*) 0;
	}

private:
	void adjustScrollPosition();
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIListBox_
