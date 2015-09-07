/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/gui/Canvas.h>

namespace awrts {
namespace gui {
Element* Canvas::getActiveElement()
{
	return active;
}

void Canvas::addElement(Element* e)
{
	e->setParent(this);
	elements.push_back(e);
}

void Canvas::removeElement(Element* e)
{
	auto element = std::find(elements.begin(), elements.end(), e);

	if (element != elements.end()) {
		elements.erase(element);
		element.removeParent();
	}
}

bool Canvas::onEvent(Event& event)
{
	Element* active = getActiveElement();
	
	if (!active)
		return true;

	return active->onEvent(event);
}

void Canvas::accept(Visitor* visitor)
{
	visitor->visit(this);
}

} // namespace gui
} // namespace awrts
