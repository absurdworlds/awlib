/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_gui_drawer_
#define _aw_gui_drawer_
#include <aw/gui/Visitor.h>

namespace aw {
namespace gui {
class Engine;

//! Drawing visitor. Used for GUI rendering.
class Drawer : public Visitor {
public:
	Drawer(Engine& engine)
		: engine(engine)
	{
	}
	virtual ~Drawer();

	virtual void visit(Element* element);
	virtual void visit(Canvas* element);
	virtual void visit(Window* element);
	virtual void visit(Widget* element);
	virtual void visit(Button* element);
private:
	void drawChildren(Canvas* element);

	Engine& engine;
};

} // namespace gui
} // namespace aw
#endif //_aw_gui_drawer_
