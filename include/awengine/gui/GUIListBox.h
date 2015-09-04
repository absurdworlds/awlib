/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUIListBox_
#define _awrts_GUIListBox_

#include <string>

#include <awrts/gui/GUIElement.h>

namespace awrts {
namespace gui {

//! List box GUI element
class GUIListBox : public GUIElement {
public:
	virtual ~GUIListBox() {};

	/*! Add an item to list box
	   \param text Text of the inserted item
	   \return Item id
	 */
	virtual u32 addItem(std::string text) = 0;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIListBox_
