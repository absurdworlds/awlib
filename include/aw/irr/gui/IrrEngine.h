/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_gui_irr_skin_
#define _aw_gui_irr_skin_
#include <aw/graphics/Color.h>
#include <aw/gui/Canvas.h>
#include <aw/gui/Widget.h>
#include <aw/gui/Drawer.h>
#include <aw/gui/Engine.h>
#include <aw/gui/Style.h>

namespace irr {
namespace video {
class IVideoDriver;
}
}

namespace aw {
namespace gui {
class IrrEngine : public Engine {
public:
	IrrEngine(irr::video::IVideoDriver* driver)
		: driver(driver)
	{}
	virtual ~IrrEngine() = default;

	virtual void drawBorder(Rect<Coordinate> const& rect, Border* style);
	virtual void drawBackground(Rect<Coordinate> const& rect, Background* style);

private:
	void drawSolidBorder(Rect<i32> rect, BorderPlain* style);
	void drawRect(Rect<i32> r, graphics::Color c);
	void drawRect(Rect<i32> r,
	              graphics::Color c1, graphics::Color c2,
	              graphics::Color c3, graphics::Color c4);
	Vector2d<i32> getScreenSize() const
	{
		return Vector2d<i32>(driver->getScreenSize().Width,
		                     driver->getScreenSize().Height);
	}

	irr::video::IVideoDriver* driver;
};
} // namespace gui
} // namespace aw
#endif //_aw_gui_irr_skin_
