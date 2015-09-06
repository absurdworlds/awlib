/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_visitor_
#define _awrts_gui_visitor_
#include <awengine/gui/Drawer.h>
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>

namespace awrts {
namespace gui {

virtual Drawer::~Drawer();

void Drawer::visit(Element* element)
{
}
void Drawer::visit(Canvas* element);
{
	Skin* skin = element->getSkin();
	skin->drawCanvas(element->getRect());
}
void Drawer::visit(Widget* element)
{
}

} // namespace gui
} // namespace awrts
#endif //_awrts_gui_visitor_
