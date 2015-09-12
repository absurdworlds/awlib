/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/utility/macro.h>
#include <awengine/core/Logger.h>
#include <awengine/graphics/Color.h>

#include <awengine/gui/Drawer.h>
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>
#include <awengine/gui/Window.h>
#include <awengine/gui/Engine.h>
#include <awengine/gui/Style.h>
namespace awrts {
namespace gui {

Drawer::~Drawer()
{
}

void Drawer::visit(Element* element)
{
	core::Logger::debug("[GUI] Drawer: Unknown Element");
}

void Drawer::visit(Canvas* element)
{
	core::Logger::debug("[GUI] Drawer: Rendering Canvas");
	//Skin* skin = element->getSkin();
	//skin->drawCanvas(element->getRect());
	drawChildren(element);
}

void Drawer::visit(Window* element)
{
	core::Logger::debug("[GUI] Drawer: Rendering Window");
	Style* style = element->getStyle();
	auto windowStyle = style->getElementStyle("window");
	if (!windowStyle) {
		core::Logger::debug("[GUI] Drawer: Can't find style");
		return; //todo : default
	}

	engine.drawBorder(element->getRect(),
		          windowStyle->getBorderStyle());

	engine.drawBackground(element->getClientRect(),
	                      windowStyle->getBackgroundStyle());

	//if (element->hasTitleBar()) {
	//}
	drawChildren(element);
}

void Drawer::visit(Widget* element)
{
	core::Logger::debug("[GUI] Drawer: Unknown Widget");
}

void Drawer::drawChildren(Canvas* element)
{
	for (auto& e : element) {
		e.accept(*this);
	}
}
} // namespace gui
} // namespace awrts
