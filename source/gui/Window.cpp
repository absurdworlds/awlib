/*
 * Copyright (C) 2014 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/core/Logger.h>

#include <awengine/gui/Window.h>
#include <awengine/gui/Visitor.h>
#include <awengine/gui/Style.h>

namespace awrts {
namespace gui {
bool Window::onEvent(Event* event)
{
	if(Canvas::onEvent(event))
		return true;

	bool consume = false;
	if (event->getType() == MouseEvent::type()) {
		consume = processEvent(event_cast<MouseEvent>(event));
	} else if (event->getType() == GUIEvent::type()) {
		consume = processEvent(event_cast<GUIEvent>(event));
	}

	return consume;
}

void Window::accept(Visitor& visitor)
{
	visitor.visit(this);
}

Rect<Coordinate> Window::getClientRect() const
{
	if (updateClientRect)
		recalculateClientRect();

	return clientRect;
}

void Window::recalculateClientRect() const
{
	clientRect = getAbsoluteRect();
	auto style = getStyle()->getElementStyle("window");
	auto border = style->getBorderStyle();

	u8 borderWidth = 0;

	switch(border->style()) {
	case Border::None:
		break;
	case Border::Solid:
	case Border::Inward:
	case Border::Outward:
		borderWidth = border->plain()->width();
		break;
	case Border::Image:
		borderWidth = border->image()->slice();
		break;
	}

	clientRect.upperLeft  += borderWidth;
	clientRect.lowerRight -= borderWidth;

	core::Logger::debug("[GUI] Window: Client rect: (" + 
			std::to_string(clientRect.upperLeft.x().fraction) + ", " +
			std::to_string(clientRect.upperLeft.y().fraction) + ", " +
			std::to_string(clientRect.lowerRight.x().fraction) + ", " +
			std::to_string(clientRect.lowerRight.y().fraction) + ").");
	core::Logger::debug("[GUI] Window: Client rect: (" + 
			std::to_string(clientRect.upperLeft.x().offset) + ", " +
			std::to_string(clientRect.upperLeft.y().offset) + ", " +
			std::to_string(clientRect.lowerRight.x().offset) + ", " +
			std::to_string(clientRect.lowerRight.y().offset) + ").");

	updateClientRect = false;
}


bool Window::processEvent(MouseEvent* event)
{
	Vector2d<f32> mousePos = event->position;
	switch (event->action) {
	case MouseEvent::Moved: {
			if (!dragging)
				break;
			Vector2d<f32> delta = mouseStart - mousePos;
			mouseStart = mousePos;
			setPosition(getPosition() + 
				    Vector2d<Coordinate>(delta[0], delta[1]));
			return true;
		}
	case MouseEvent::LButtonDown:
		mouseStart = mousePos;
		dragging = isDraggable;
		return true;
	case MouseEvent::LButtonUp:
		dragging = false;
		return true;
	default:
		break;
	}
	return false;
}

bool Window::processEvent(GUIEvent* event)
{
	switch (event->action) {
	case GUIEvent::Focused:
		if (getParent()) {
			getParent()->toCanvas()->bringToFront(this);
		}
		return true;
	case GUIEvent::FocusLost:
		dragging = false;
		return true;
	default:
		break;
	}
	return false;
}
/*
void Window::move(Vector2d<f32> delta)
{
	// TODO: check if within the parent's rectangle
}*/
} // namespace gui
} // namespace awrts
