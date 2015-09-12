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

#include <awengine/utility/toIrr/color.h>
#include <awengine/utility/toIrr/rect.h>

#include <awengine/core/Logger.h>

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

Rect<i32> IrrEngine::toPixels(Rect<Coordinate> const& rect)
{
	auto dim = driver->getScreenSize();
	Rect<i32> tmp;
	tmp.upperLeft.x()  = rect.upperLeft.x().fraction * dim.Width;
	tmp.upperLeft.x() += rect.upperLeft.x().offset;
	tmp.upperLeft.y()  = rect.upperLeft.y().fraction * dim.Height;
	tmp.upperLeft.y() += rect.upperLeft.y().offset;
	tmp.lowerRight.x()  = rect.lowerRight.x().fraction * dim.Width;
	tmp.lowerRight.x() += rect.lowerRight.x().offset;
	tmp.lowerRight.y()  = rect.lowerRight.y().fraction * dim.Height;
	tmp.lowerRight.y() += rect.lowerRight.y().offset;

	core::Logger::debug("[GUI] IrrEngine: Client rect: (" +
			std::to_string(rect.upperLeft.x().fraction) + ", " +
			std::to_string(rect.upperLeft.y().fraction) + ", " +
			std::to_string(rect.lowerRight.x().fraction) + ", " +
			std::to_string(rect.lowerRight.y().fraction) + ").");
	core::Logger::debug("[GUI] IrrEngine: Client rect: (" +
			std::to_string(rect.upperLeft.x().offset) + ", " +
			std::to_string(rect.upperLeft.y().offset) + ", " +
			std::to_string(rect.lowerRight.x().offset) + ", " +
			std::to_string(rect.lowerRight.y().offset) + ").");
	return tmp;
}

void IrrEngine::drawBorder(Rect<Coordinate> const& rect, Border* style)
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

void IrrEngine::drawSolidBorder(Rect<i32> rect, BorderPlain* style)
{
	auto color = style->color();
	auto width = style->width();

	Rect<i32> tmp;

	if (style->style() == Border::Inward) {
		u32 rest = width - width / 2;

		// top dark
		tmp = rect;
		tmp.lowerRight.y() = tmp.upperLeft.y() + rest;
		drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// top bright
			tmp = rect;
			tmp.lowerRight.y() = tmp.upperLeft.y() + width;
			tmp.upperLeft += rest;
			drawRect(tmp, graphics::darken(color, 127));
		}
		
		// left dark
		tmp = rect;
		tmp.lowerRight.x() = tmp.upperLeft.x() + rest;
		drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// left bright
			tmp = rect;
			tmp.lowerRight.x() = tmp.upperLeft.x() + width;
			tmp.upperLeft += rest;
			drawRect(tmp, graphics::darken(color, 127));
		}
	} else {
		// top
		tmp = rect;
		tmp.lowerRight.y() = tmp.upperLeft.y() + width;
		drawRect(tmp, color);

		// left
		tmp = rect;
		tmp.lowerRight.x() = tmp.upperLeft.x() + width;
		drawRect(tmp, color);
	}


	if (style->style() == Border::Outward) {
		u32 rest = width - width / 2;
		// bottom dark
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - rest;
		drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// bottom bright
			tmp = rect;
			tmp.upperLeft.y() = tmp.lowerRight.y() - width;
			tmp.lowerRight.y() = tmp.lowerRight.y() - rest;
			tmp.lowerRight.x() -= rest; 
			drawRect(tmp, graphics::darken(color, 127));
		}

		// right dark
		tmp = rect;
		tmp.upperLeft.x() = tmp.lowerRight.x() - rest;
		drawRect(tmp, graphics::darken(color, 200));

		if ((width / 2) > 0) {
			// right bright
			tmp = rect;
			tmp.upperLeft.x() = tmp.lowerRight.x() - width;
			tmp.lowerRight.x() = tmp.lowerRight.x() - rest;
			tmp.lowerRight.y() -= rest;
			drawRect(tmp, graphics::darken(color, 127));
		}
	} else {
		// bottom
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - width;
		tmp.upperLeft.x() += width;
		drawRect(tmp, color);

		// right
		tmp = rect;
		tmp.upperLeft.x() = tmp.lowerRight.x() - width;
		tmp.upperLeft.y() += width;
		drawRect(tmp, color);
	}
}

void IrrEngine::drawBackground(Rect<Coordinate> const& rect, Background* style)
{
	switch (style->style()) {
	case Background::None:
		core::Logger::debug("[GUI] IrrEngine: Drawing empty bg");
		return;
	case Background::Solid:
		core::Logger::debug("[GUI] IrrEngine: Drawing solid bg");
		drawRect(toPixels(rect), style->solid()->color());
		break;
	case Background::Gradient: {
			core::Logger::debug("[GUI] IrrEngine: Drawing gradient bg");
			auto s = style->gradient();
			auto c1 = s->color(Corner::TopLeft);
			auto c2 = s->color(Corner::BottomLeft);
			auto c3 = s->color(Corner::BottomRight);
			auto c4 = s->color(Corner::TopRight);
			drawRect(toPixels(rect), c1, c2, c3, c4);
		}
		break;
	case Background::Image:
		// drawImageBorder(toPixels(rect), style->image());
		break;
	}
}

void IrrEngine::drawRect(Rect<i32> r, graphics::Color c)
{
	auto rect = toIrr(r);
	auto color = toIrr(c);
	driver->draw2DRectangle(color, rect);
}

void IrrEngine::drawRect(Rect<i32> r,
	                 graphics::Color c1, graphics::Color c2,
	                 graphics::Color c3, graphics::Color c4)
{
	core::Logger::debug("[GUI] IrrEngine: Drawing rect: (" + 
			std::to_string(r.upperLeft.x()) + ", " +
			std::to_string(r.upperLeft.y()) + ", " +
			std::to_string(r.lowerRight.x()) + ", " +
			std::to_string(r.lowerRight.y()) + ").");
	auto rect = toIrr(r);
	auto lu = toIrr(c1);
	auto ld = toIrr(c2);
	auto rd = toIrr(c3);
	auto ru = toIrr(c4);
	driver->draw2DRectangle(rect, lu, ru, ld, rd);
}

	/*
	// client area for background
	rect = r;
	rect.UpperLeftCorner.X +=1;
	rect.UpperLeftCorner.Y +=1;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y -= 2;

	const irr::video::SColor c1 = irr::video::SColor(255,100,100,100).getInterpolated ( 0xFFFFFFFF, 0.9f );
	const irr::video::SColor c2 = irr::video::SColor(255,150,150,150).getInterpolated ( 0xFFFFFFFF, 0.8f );

	driver->draw2DRectangle(rect, c1, c1, c2, c2);
	*/

/*
void IrrRenderer::drawTitleBar(irr::core::rect<irr::s32> r)
{
	rect = r;
	rect.UpperLeftCorner.X += 2;
	rect.UpperLeftCorner.Y += 2;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + getSize(EGDS_WINDOW_BUTTON_WIDTH) + 2;

	const irr::video::SColor c = titleBarColor.getInterpolated( irr::video::SColor(titleBarColor.getAlpha(),255,255,255), 0.8f);
	driver->draw2DRectangle(rect, titleBarColor, titleBarColor, c, c);
}*/
} // namespace gui
} // namespace awrts
