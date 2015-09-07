/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_canvas_
#define _awrts_GUI_canvas_
#include <awengine/gui/Element.h>
#include <awengine/gui/Container.h>

namespace awrts {
namespace gui {
class Canvas : public Element, Container {
public:
	Canvas();
	virtual ~Canvas() = default;

	virtual void addElement(std::unique_ptr<Element> e)
	{
		Container::addElement(std::move(e));
		e->setParent(this);
	}

	/*!
	 * Get currently active element (which is
	 * currently being interacted with).
	 */
	virtual Element* getActiveElement();

	virtual bool onEvent(Event* event);
	virtual void accept(Visitor& visitor);

	virtual Canvas* toCanvas()
	{
		return this;
	}

	virtual Widget* toWidget()
	{
		return nullptr
	}
};


} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_canvas_
