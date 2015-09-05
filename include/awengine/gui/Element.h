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

#include <awrts/common/types.h>
#include <awrts/common/hidden_impl.h>
#include <awengine/common/EventListener.h>

namespace awrts {
namespace gui {
class Canvas;

//! Base class for GUI elements
class Element : EventListener {
public:
	virtual ~Element() {}

	/*!
	 * Returns pointer to canvas, which contains this
	 * element.
	 */
	virtual Canvas* getCanvas() const = 0;

	virtual void setPosition(Vector2d<f32> position) = 0;
	virtual void setWidth(f32 width) = 0;
	virtual void setHeight(f32 height) = 0;

	virtual Vector2d<f32> getPosition() = 0;
	virtual Vector2d<f32> getAbsolutePosition() = 0;

	virtual f32 getWidth() = 0;
	virtual f32 getHeight() = 0;

	/*!
	 * Receive event.
	 * Most commonly used to receive user input.
	 */
	virtual bool onEvent(Event* event) = 0;

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(Element);
private:
	Rect<f32> rect;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIElement_
