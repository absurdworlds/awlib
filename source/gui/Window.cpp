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

	updateClientRect = false;
}

inline Vector2d<Coordinate> localToWorld(
               Vector2d<Coordinate> const& local,
	       Rect<Coordinate> const& parent)
{
	auto width  = parent.getWidth();
	auto height = parent.getHeight();
	auto temp = parent.upperLeft;

	temp.x() +=  width * local.x().fraction + local.x().offset;
	temp.y() += height * local.y().fraction + local.y().offset;

	return temp;
}

inline Coordinate worldToLocal(
		Coordinate const& world,
		Coordinate const& origin,
		Coordinate const& width)
{
	Coordinate temp = world - origin;
	if (math::equals(width.fraction, 0.0f)) {
		return temp;
	} else if(math::equals(width.offset,0.0f)) {
		temp.fraction /= width.fraction;
		return temp;
	}

	temp /= width;
	i32 offset = width.offset * (temp.offset - temp.fraction);

	temp.offset = offset;
	return temp;
}

inline Vector2d<Coordinate> worldToLocal(
               Vector2d<Coordinate> const& world,
	       Rect<Coordinate> const& parent)
{
	auto width  = parent.getWidth();
	auto height = parent.getHeight();

	Vector2d<Coordinate> temp(0,0);
	temp.x() = worldToLocal(world.x(), parent.upperLeft.x(), width);
	temp.y() = worldToLocal(world.y(), parent.upperLeft.y(), height);

	return temp;
}

bool Window::mouseMoved(MouseEvent* event)
{
	if (!dragging)
		return false;

	auto const& mousePos = event->position;
	auto const& bounds = event->bounds;
	auto parentRect = getParent()->getAbsoluteRect();

	Vector2d<Coordinate> pos(mousePos.x(), mousePos.y());
	pos   = worldToLocal(pos, parentRect);

	Vector2d<Coordinate> start(mouseStart.x(), mouseStart.y());
	start = worldToLocal(start, parentRect);

	mouseStart = mousePos;

	Vector2d<Coordinate> delta = pos - start;

	auto oldPos = getPosition();
	auto newPos = oldPos + delta;

	setPosition(newPos);

	auto absoluteRect = toPixels(getAbsoluteRect(), bounds);
	auto absoluteParentRect = toPixels(parentRect, bounds);

	if (absoluteRect.upperLeft.x() < absoluteParentRect.upperLeft.x() ||
	    absoluteRect.upperLeft.y() < absoluteParentRect.upperLeft.y() ||
	    absoluteRect.lowerRight.x() > absoluteParentRect.lowerRight.x() ||
	    absoluteRect.lowerRight.y() > absoluteParentRect.lowerRight.y()) {
		setPosition(oldPos);
		return true;
	}
	return true;
}

bool Window::processEvent(MouseEvent* event)
{
	switch (event->action) {
	case MouseEvent::Moved:
		return mouseMoved(event);
	case MouseEvent::LButtonDown:
		mouseStart = event->position;
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
