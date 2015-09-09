/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <Irrlicht/IVideoDriver.h>
#include <Irrlicht/IGUISkin.h>

#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>
#include <awengine/gui/Drawer.h>
#include "IrrEngine.h"

namespace awrts {
namespace gui {
/*
IrrSkin::~IrrSkin()
{
}*/

irr::core::rect<irr::s32> toIrr(Rect<f32> awRect)
{
	return irr::core::rect<irr::s32>(
	       (int)awRect.upperLeft.x(), (int)awRect.upperLeft.y(),
	       (int)awRect.lowerRight.x(), (int)awRect.lowerRight.y());
}

irr::video::SColor toIrr(graphics::Color color)
{
	return irr::video::SColor(color.a(), color.r(), color.g(), color.b());
}

irr::core::rect<irr::s32> toIrr(Rect<i32> awRect)
{
	return irr::core::rect<irr::s32>(
	       awRect.upperLeft.x(),  awRect.upperLeft.y(),
	       awRect.lowerRight.x(), awRect.lowerRight.y());
}

Rect<i32> toPixels(Rect<f32> const& rect)
{
	Vector2d<i32> screen = toAW(driver->getScreenSize());
	Rect<i32> tmp;
	rect.upperLeft.x() = w.upperLeft.x() * screen.x();
	rect.upperLeft.y() = w.upperLeft.y() * screen.y();
	rect.lowerRight.x() = w.lowerRight.x() * screen.x();
	rect.lowerRight.y() = w.lowerRight.y() * screen.y();
	return tmp;
}

void IrrEngine::drawBorder(Rect<f32> const& rect, Border const* style)
{
	switch (style->style()) {
	case Border::None:
		return;
	case Border::Solid:
	case Border::Outward:
	case Border::Inward:
		drawSolidBorder(toPixels(rect), style->plain());
		break;
	case Border::Image:
		// drawImageBorder(toPixels(rect), style->image());
		break;
	}
}

void IrrSkin::drawSolidBorder(Rect<i32> rect, BorderSolid const* style)
{
	auto color = style->color();
	auto width = style->width();

	Rect<i32> tmp;

	if (style->style() == Border::Inward) {
		u32 rest = width - width / 2;

		// top dark
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - rest;
		renderer.drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// top bright
			tmp = rect;
			tmp.lowerRight.y() = tmp.upperLeft.y() + width;
			tmp.upperLeft += rest;
			renderer.drawRect(tmp, graphics::darken(color, 127));
		}
		
		// left dark
		tmp = rect;
		tmp.lowerRight.x() = tmp.upperLeft.x() + rest;
		renderer.drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// left bright
			tmp = rect;
			tmp.lowerRight.x() = tmp.upperLeft.x() + width;
			tmp.upperLeft += rest;
			renderer.drawRect(tmp, graphics::darken(color, 127));
		}
	} else {
		// top
		tmp = rect;
		tmp.lowerRight.y() = tmp.upperLeft.y() + width;
		renderer.drawRect(tmp, color);

		// left
		tmp = rect;
		tmp.lowerRight.x() = tmp.upperLeft.x() + width;
		renderer.drawRect(tmp, color);
	}


	if (style->style() == Border::Outward) {
		// bottom dark
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - rest;
		renderer.drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// bottom bright
			tmp = rect;
			tmp.upperLeft.y() = tmp.lowerRight.y() - width;
			tmp.lowerRight.y() = tmp.lowerRight.y() - rest;
			tmp.lowerRight.x() -= rest; 
			renderer.drawRect(tmp, graphics::darken(color, 127));
		}

		// right dark
		tmp = rect;
		tmp.upperLeft.x() = tmp.lowerRight.x() - rest;
		renderer.drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// right bright
			tmp = rect;
			tmp.upperLeft.x() = tmp.lowerRight.x() - width;
			tmp.lowerRight.x() = tmp.lowerRight.x() - rest;
			tmp.lowerRight.y() -= rest;
			renderer.drawRect(tmp, graphics::darken(color, 127));
		}
	} else {
		// bottom
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - width;
		renderer.drawRect(tmp, color);

		// right
		tmp = rect;
		tmp.upperLeft.x() = tmp.lowerRight.x() - width;
		renderer.drawRect(tmp, color);
	}
}

void IrrEngine::drawRect(Rect<i32> r, graphics::Color c)
{
	auto rect = toIrr(r);
	auto color = toIrr(c);
	Driver->draw2DRectangle(color, rect);

	/*
	// client area for background
	rect = r;
	rect.UpperLeftCorner.X +=1;
	rect.UpperLeftCorner.Y +=1;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y -= 2;

	const irr::video::SColor c1 = irr::video::SColor(255,100,100,100).getInterpolated ( 0xFFFFFFFF, 0.9f );
	const irr::video::SColor c2 = irr::video::SColor(255,150,150,150).getInterpolated ( 0xFFFFFFFF, 0.8f );

	Driver->draw2DRectangle(rect, c1, c1, c2, c2);
	*/
}

/*
void IrrRenderer::drawTitleBar(irr::core::rect<irr::s32> r)
{
	rect = r;
	rect.UpperLeftCorner.X += 2;
	rect.UpperLeftCorner.Y += 2;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + getSize(EGDS_WINDOW_BUTTON_WIDTH) + 2;

	const irr::video::SColor c = titleBarColor.getInterpolated( irr::video::SColor(titleBarColor.getAlpha(),255,255,255), 0.8f);
	Driver->draw2DRectangle(rect, titleBarColor, titleBarColor, c, c);
}*/
} // namespace gui
} // namespace awrts
