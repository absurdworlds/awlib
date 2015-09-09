/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/gui/Drawer.h>
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>
#include <awengine/gui/Window.h>
#include <awengine/gui/Skin.h>
#include <awengine/utility/macro.h>
namespace awrts {
namespace gui {

Drawer::~Drawer()
{
}

void Drawer::visit(Element* element)
{
}
void Drawer::visit(Canvas* element)
{
	//Skin* skin = element->getSkin();
	//skin->drawCanvas(element->getRect());
	for (auto& e : element) {
		e.accept(*this);
	}
}
void Drawer::visit(Window* element)
{
	Skin* skin = element->getSkin();
	skin->draw3DBorderInset(element->getRect());
}
void Drawer::visit(Widget* element)
{
}

} // namespace gui
} // namespace awrts
