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
#include <awengine/math/Rect.h>
#include <awengine/common/EventListener.h>

namespace awrts {
namespace gui {
class Canvas;
class Skin;
class Visitor;

//! Base class for GUI elements
class Element : public EventListener {
public:
	virtual ~Element() {}

	/*!
	 * Returns pointer to canvas, which contains this
	 * element.
	 */
	virtual Canvas* getParent() const
	{
		return reinterpret_cast<Canvas*>(parent);
	}

	virtual void setPosition(Vector2d<f32> position)
	{
		rect.setPosition(position);
	}
	virtual void setWidth(f32 width)
	{
		rect.setWidth(width);
	}
	virtual void setHeight(f32 height)
	{
		rect.setHeight(height);
	}

	virtual Vector2d<f32> getPosition()
	{
		return rect.getUpperLeft();
	}

	virtual Vector2d<f32> getAbsolutePosition()
	{
		if (!parent)
			return getPosition();

		return parent->getAbsolutePosition() + getPosition();
	}

	virtual f32 getWidth() const
	{
		return rect.getWidth();
	}
	
	virtual f32 getHeight() const
	{
		return rect.getHeight();
	}

	virtual Skin* getSkin() const
	{
		if (!skin)
			return parent->getSkin();

		return skin;
	}

	virtual void setSkin(Skin* newSkin)
	{
		// TODO: if newSkin == parent->skin, should it be reset to 0?
		skin = newSkin;
	}

	virtual void accept(gui::Visitor& visitor) = 0;

	/*!
	 * Receive event.
	 * Most commonly used to receive user input.
	 */
	virtual bool onEvent(Event* event) = 0;
protected:
	Element()
		: parent(nullptr)
	{
	}

	Element(Element* parent)
		: parent(parent)
	{
	}
private:
	Rect<f32> rect;
	Skin* skin;
	Element* parent;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIElement_
