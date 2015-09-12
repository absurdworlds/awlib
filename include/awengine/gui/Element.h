/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUIElement_
#define _awrts_GUIElement_
#include <string>

#include <awengine/common/types.h>
#include <awengine/common/EventListener.h>
#include <awengine/math/Rect.h>
#include <awengine/gui/Coordinate.h>
#include <awengine/gui/KeyboardEvent.h>
#include <awengine/gui/MouseEvent.h>
#include <awengine/gui/GUIEvent.h>

namespace awrts {
namespace gui {
class Canvas;
class Widget;
class Style;
class Visitor;

//! Base class for GUI elements
class Element : public EventListener {
public:
	virtual ~Element() = default;

	/*!
	 * Returns pointer to parent element.
	 */
	virtual Element* getParent() const
	{
		return parent;
	}

	virtual Vector2d<Coordinate> getPosition()
	{
		return rect.getUpperLeft();
	}

	virtual Vector2d<Coordinate> getAbsolutePosition()
	{
		return absoluteRect.getUpperLeft();
	}

	virtual Coordinate getWidth() const
	{
		return rect.getWidth();
	}
	
	virtual Coordinate getHeight() const
	{
		return rect.getHeight();
	}

	virtual Rect<Coordinate> getRect() const
	{
		return rect;
	}

	virtual Rect<Coordinate> getAbsoluteRect() const
	{
		// Absolute rect needs updating (element moved,
		// parent moved, etc)
		if (updateAbsoluteRect)
			absoluteRect = parent->getAbsoluteRect() + getRect();

		return absoluteRect;
	}

	virtual Style* getStyle() const
	{
		if (!style)
			return parent->getStyle();

		return style;
	}

	virtual void setPosition(Vector2d<Coordinate> position)
	{
		rect.setPosition(position);
		invalidate();
	}

	virtual void setWidth(Coordinate width)
	{
		rect.setWidth(width);
		invalidate();
	}

	virtual void setHeight(Coordinate height)
	{
		rect.setHeight(height);
		invalidate();
	}

	virtual void setRect(Rect<Coordinate> newRect)
	{
		rect = newRect;
		invalidate();
	}

	void setParent(Element* newParent)
	{
		parent = newParent;
		invalidate();
	}

	void removeParent()
	{
		parent = nullptr;
		invalidate();
	}

	virtual void setStyle(Style* newStyle)
	{
		// TODO: if newStyle == parent->style, should it be reset to 0?
		style = newStyle;
		invalidate();
	}


	virtual Canvas* toCanvas() = 0;
	virtual Widget* toWidget() = 0;

	/*!
	 * Accept a GUI Element Visitor. Useful for performing
	 * various operations on Elements and their children.
	 */
	virtual void accept(gui::Visitor& visitor) = 0;

	/*!
	 * Receive event.
	 * Most commonly used to receive user input.
	 * \return
	 *      true if event was consumed.
	 */
	virtual bool onEvent(Event* event) = 0;

	virtual void invalidate()
	{
		updateAbsoluteRect = true;
	}
protected:
	Element()
		: parent(nullptr)
	{
	}
private:
	Rect<Coordinate> rect;

	bool updateAbsoluteRect;
	mutable Rect<Coordinate> absoluteRect;

	Style* style;
	Element* parent;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIElement_
