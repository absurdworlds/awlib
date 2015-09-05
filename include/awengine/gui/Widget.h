/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_widget_
#define _awrts_gui_widget_
#include <awengine/gui/Element.h>

namespace awrts {
namespace gui {
//! Base class for GUI widget
class Widget : Element {
public:
	virtual ~Widget() {};
};

} // namespace gui
} // namespace awrts
#endif //_awrts_gui_widget_
