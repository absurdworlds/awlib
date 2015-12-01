/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIElement_
#define _aw_GUIElement_
#include <string>

#include <aw/common/types.h>
#include <aw/common/EventListener.h>
#include <aw/math/Rect.h>
#include <aw/gui/Coordinate.h>
#include <aw/gui/KeyboardEvent.h>
#include <aw/gui/MouseEvent.h>
#include <aw/gui/GUIEvent.h>
#include <aw/core/Logger.h>

namespace aw {
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
			recalculateAbsoluteRect();

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

	void setName(std::string name)
	{
	}
protected:
	Element()
		: parent(nullptr), updateAbsoluteRect(true)
	{
	}
private:
	void recalculateAbsoluteRect() const
	{
		if (!getParent()) {
			absoluteRect = getRect();
			return;
		}
		
		// compute parent rect
		Rect<Coordinate> parentRect = parent->getAbsoluteRect();
		Coordinate height = parentRect.getHeight();
		Coordinate width  = parentRect.getWidth();

		// references to local rect coordinates, for convenience
		auto& ulx = rect.upperLeft.x();
		auto& uly = rect.upperLeft.y();
		auto& lrx = rect.lowerRight.x();
		auto& lry = rect.lowerRight.y();

		// go from local coordinates to absolute (move origin)
		Rect<Coordinate> temp;
		temp.upperLeft  = parentRect.upperLeft;
		temp.lowerRight = parentRect.upperLeft;

		// compute using Coordinate's definition:
		// parent_dimension * fraction + offset
		temp.upperLeft.x()  += width  * ulx.fraction + ulx.offset;
		temp.upperLeft.y()  += height * uly.fraction + uly.offset;
		temp.lowerRight.x() += width  * lrx.fraction + lrx.offset;
		temp.lowerRight.y() += height * lry.fraction + lry.offset;

		absoluteRect = temp;
		updateAbsoluteRect = false;
	}

	Rect<Coordinate> rect;

	mutable bool updateAbsoluteRect;
	mutable Rect<Coordinate> absoluteRect;

	Style* style;
	Element* parent;
};

inline bool pointWithinElement(Vector2d<i32> point,
                               Element const& element,
                               Vector2d<i32> screen)
{
	auto rect = element.getAbsoluteRect();
	Rect<i32> screenRect = toPixels(rect, screen);
	return pointWithinRect(point, screenRect);
}

} // namespace gui
} // namespace aw
#endif //_aw_GUIElement_
