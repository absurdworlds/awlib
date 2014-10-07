/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IGUIListBox_
#define _hrengin_IGUIListBox_

#include <string>

#include <hrengin/gui/IGUIElement.h>

namespace hrengin {
namespace gui {

//! List box GUI element
class IGUIListBox : public IGUIElement {
public:
	virtual ~IGUIListBox() {};

	/*! Add an item to list box
	   \param text Text of the inserted item
	   \return Item id
	 */
	virtual u32 addItem(std::string text) = 0;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIListBox_
