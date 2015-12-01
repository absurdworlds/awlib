/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_skin_
#define _aw_GUI_skin_
#include <aw/gui/Element.h>
#include <aw/math/Rect.h>

namespace aw {
namespace gui {
class Border;
class Background;

class Engine {
public:
	virtual ~Engine() = default;

	virtual void drawBorder(Rect<Coordinate> const& rect,
	                        Border* style) = 0;
	virtual void drawBackground(Rect<Coordinate> const& rect,
	                            Background* style) = 0;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUI_skin_
