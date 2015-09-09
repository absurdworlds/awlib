/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_irr_skin_
#define _awrts_gui_irr_skin_
#include <awengine/graphics/Color.h>
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>
#include <awengine/gui/Drawer.h>
#include <awengine/gui/Engine.h>
#include <awengine/gui/Style.h>

#include <Irrlicht/rect.h>
namespace irr {
namespace video {
class IVideoDriver;
}
}

namespace awrts {
namespace gui {
class IrrRenderer {
public:
	IrrRenderer(irr::video::IVideoDriver* driver)
		: Driver(driver)
	{}
	void drawRect(Rect<i32> r, graphics::Color c);
	void drawTitleBar(irr::core::rect<irr::s32> r);
private:
	irr::video::IVideoDriver* Driver;
};

class IrrEngine : public Engine {
public:
	IrrSkin(irr::video::IVideoDriver* driver)
		: renderer(driver)
	{}
	virtual ~IrrSkin() = default;

	virtual void drawBorder(Rect<f32> const& rect, Border const* style);
	virtual void draw3DBorderInset(Rect<f32> const& rect,
	                               graphics::Color color,
				       u32 width);
	virtual void drawWindowTitleBar(Rect<f32> const& rect);
private:
	IrrRenderer renderer;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_gui_irr_skin_
