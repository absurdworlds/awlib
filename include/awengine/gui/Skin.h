/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_skin_
#define _awrts_GUI_skin_
#include <awengine/gui/Element.h>
#include <awengine/math/Rect.h>

namespace awrts {
namespace gui {
class Skin {
public:
	virtual ~Skin() = default;

	virtual void drawCanvas(Rect<f32> const& rect) = 0;
	virtual void draw3DBorderInset(Rect<f32> const& rect) = 0;
	virtual void drawWindowTitleBar(Rect<f32> const& rect) = 0;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_skin_
