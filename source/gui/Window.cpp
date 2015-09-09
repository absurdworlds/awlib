/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/gui/Window.h>
#include <awengine/gui/Visitor.h>


namespace awrts {
namespace gui {
bool Window::onEvent(Event* event)
{
	return true;
}
void Window::accept(Visitor& visitor)
{
	visitor.visit(this);
}
} // namespace gui
} // namespace awrts
