/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_canvas_
#define _awrts_GUI_canvas_
#include <awengine/gui/Element.h>

namespace awrts {
namespace gui {
class Canvas : Element {
public:
	virtual ~Canvas() {};

	/*!
	 * Get currently active element (which is
	 * currently being interacted with).
	 */
	virtual Element* getActiveElement();

	/*!
	 * Add a child element
	 */
	virtual void addElement(Element* e) = 0;

	/*!
	 * Remove child
	 */
	virtual void removeElement(Element* e) = 0;

	virtual void draw() = 0;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_canvas_
