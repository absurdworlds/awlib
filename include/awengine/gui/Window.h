/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUIWindow_
#define _awrts_GUIWindow_
#include <awengine/gui/Canvas.h>

namespace awrts {
namespace gui {

//! GUI window
class Window : public Canvas {
public:
	virtual ~Window() {};
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIWindow_
