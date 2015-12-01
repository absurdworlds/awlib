/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_gui_widget_
#define _aw_gui_widget_
#include <aw/gui/Element.h>

namespace aw {
namespace gui {
//! Base class for GUI widget
class Widget : public Element {
public:
	virtual ~Widget() {};
	virtual Canvas* toCanvas()
	{
		return nullptr;
	}
	virtual Widget* toWidget()
	{
		return this;
	}
};

} // namespace gui
} // namespace aw
#endif //_aw_gui_widget_
