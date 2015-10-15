/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/core/Logger.h>
#include <aw/graphics/Color.h>

#include <aw/utility/range_adaptors.h>

#include <aw/gui/Drawer.h>
#include <aw/gui/Canvas.h>
#include <aw/gui/Widget.h>
#include <aw/gui/Window.h>
#include <aw/gui/Engine.h>
#include <aw/gui/Style.h>

namespace aw {
namespace gui {
auto getStyle(Style* style, std::string const& name)
{
	auto elementStyle = style->getElementStyle(name);

	if (!elementStyle) {
		core::Logger::debug("[GUI] Drawer: Can't find style for “" +
		                    name + "”.");
		return style->getDefaultStyle();
	}

	return elementStyle;
}

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
	drawChildren(element);
}

void Drawer::visit(Window* element)
{
	auto style = getStyle(element->getStyle(), "window");

	engine.drawBorder(element->getAbsoluteRect(),
	                  style->getBorderStyle());

	engine.drawBackground(element->getClientRect(),
	                      style->getBackgroundStyle());

	//if (element->hasTitleBar()) {
	//}
	drawChildren(element);
}

void Drawer::visit(Widget* element)
{
	core::Logger::debug("[GUI] Drawer: Unknown Widget");
}

void Drawer::visit(Button* button)
{
	auto style = getStyle(button->getStyle(),
	                      button->isPressed() ?
	                      "buttonPressed" : "button");

	engine.drawBackground(button->getClientRect(),
	                      style->getBackgroundStyle());
	engine.drawBorder(button->getAbsoluteRect(),
	                  style->getBorderStyle());
}

// TODO: replace pointer with reference
void Drawer::drawChildren(Canvas* element)
{
	for (auto& e : element) {
		e.accept(*this);
	}
}

} // namespace gui
} // namespace aw
