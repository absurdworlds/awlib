/*
 * Copyright (C) 2014 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIWindow_
#define _aw_GUIWindow_
#include <aw/gui/Canvas.h>

namespace aw {
namespace gui {

//! Typical “Window” with a title bar
class Window : public Canvas {
public:
	Window() = default;
	virtual ~Window() = default;

	virtual bool onEvent(Event* event);
	virtual void accept(Visitor& visitor);

	virtual Rect<Coordinate> getClientRect() const;

	virtual void setDraggable(bool draggable)
	{
		isDraggable = draggable;
	}

	virtual void invalidate()
	{
		Canvas::invalidate();
		updateClientRect = true;
	}
protected:
	virtual void recalculateClientRect() const;
private:
	bool processEvent(MouseEvent* event);
	bool mouseMoved(MouseEvent* event);
	//bool processEvent(KeyboardEvent* event);
	bool processEvent(GUIEvent* event);

	mutable bool updateClientRect;
	mutable Rect<Coordinate> clientRect;

	bool dragging;
	bool resizing;
	Vector2d<f32> mouseStart;

	bool hasTitlebar;
	bool isDraggable;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUIWindow_
