/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Visitor.h>
#include <awengine/core/Logger.h>

namespace awrts {
namespace gui {
Element* Canvas::getActiveElement()
{
	return active;
}

void Canvas::addElement(std::unique_ptr<Element> e)
{
	core::Logger::debug("[GUI] Canvas: Adding Element");
	e->setParent(this);
	elements.push_back(std::move(e));
}

std::unique_ptr<Element> Canvas::removeElement(Element* e)
{
	core::Logger::debug("[GUI] Canvas: Removing Element");
	auto compare = [&e] (std::unique_ptr<Element>& ptr) {
		return ptr.get() == e;
	};

	auto element = std::find_if(elements.begin(), elements.end(), compare);

	if (element != elements.end()) {
		auto temp = std::move(*element);
		temp->removeParent();

		elements.erase(element);

		return std::move(temp);
	}

	return nullptr;
}

bool Canvas::onEvent(Event* event)
{
	Element* active = getActiveElement();
	
	if (!active)
		return true;

	return active->onEvent(event);
}

void Canvas::accept(Visitor& visitor)
{
	visitor.visit(this);
}

} // namespace gui
} // namespace awrts
