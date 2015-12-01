/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_gui_visitor_
#define _aw_gui_visitor_
namespace aw {
namespace gui {
class Element;
class Canvas;
class Widget;
class Window;

//! Base class for GUI visitor (see Visitor pattern)
class Visitor {
public:
	virtual ~Visitor() = default;

	virtual void visit(Element* element) = 0;
	virtual void visit(Canvas* element) = 0;
	virtual void visit(Window* element) = 0;
	virtual void visit(Widget* element) = 0;
};

} // namespace gui
} // namespace aw
#endif //_aw_gui_visitor_
