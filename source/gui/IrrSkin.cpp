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
#include "IrrSkin.h"

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
	return irr::core::rect<irr::s32>(color.getARGB());
}

void IrrSkin::drawCanvas(Rect<f32> const& rect)
{
}

void IrrSkin::draw3DBorderInset(Rect<f32> const& w, graphics::Color color, u32 width)
{
	//Rect screen = /*wtf*/->getScreenDimensions();
	Vector2d<i32> screen(800,600);
	Rect<i32> rect;
	Rect<f32> tmp;
	rect.upperLeft.x() = w.upperLeft.x() * screen.x();
	rect.upperLeft.y() = w.upperLeft.y() * screen.y();
	rect.lowerRight.x() = w.lowerRight.x() * screen.x();
	rect.lowerRight.y() = w.lowerRight.y() * screen.y();

	// top
	tmp = rect;
	tmp.lowerRight.y() = tmp.upperLeft.y() + width;
	renderer.drawRect(tmp, color);

	// left
	tmp = rect;
	tmp.lowerRight.x() = tmp.upperLeft.x() + width;
	renderer.drawRect(tmp, color);

	u32 rest = width - width / 2;

	if (width / 2 > 0) {
		// bottom bright
		tmp = rect;
		tmp.upperLeft.y() = tmp.lowerRight.y() - width / 2;
		renderer.drawRect(tmp, graphics::darken(color, 0.5));
	}

	// bottom dark
	tmp = rect;
	tmp.upperLeft.y() = tmp.lowerRight.y() - rest;
	renderer.drawRect(tmp, graphics::darken(color, 0.2));
	
	if (width / 2 > 0) {
		// right bright
		tmp = rect;
		tmp.upperLeft.x() = tmp.lowerRight.x() - width / 2;
		renderer.drawRect(tmp, graphics::darken(color, 0.5));
	}

	// right dark
	tmp = rect;
	tmp.upperLeft.x() = tmp.lowerRight.x() - rest;
	renderer.drawRect(tmp, graphics::darken(color, 0.2));
}
#if 0
void IrrSkin::draw3DBorderOutset(Rect<f32> const& w)
{
	Rect screen = /*wtf*/->getScreenDimensions();
	Rect rect;
	rect.upperLeft.x() = w.upperLeft.x() * screen.upperLeft.x();
	rect.upperLeft.y() = w.upperLeft.y() * screen.upperLeft.y();
	rect.lowerRight.x() = w.lowerRight.x() * screen.lowerRight.x();
	rect.lowerRight.y() = w.lowerRight.y() * screen.lowerRight.y();

	renderer->drawWindowBackground(toIrr(rect));
}
#endif

void IrrSkin::drawWindowTitleBar(Rect<f32> const& rect)
{
}


void IrrRenderer::drawRect(Rect<i32> r, graphics::Color c)
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

void IrrRenderer::drawTitleBar(irr::core::rect<irr::s32> r)
{
/*	rect = r;
	rect.UpperLeftCorner.X += 2;
	rect.UpperLeftCorner.Y += 2;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + getSize(EGDS_WINDOW_BUTTON_WIDTH) + 2;

	const irr::video::SColor c = titleBarColor.getInterpolated( irr::video::SColor(titleBarColor.getAlpha(),255,255,255), 0.8f);
	Driver->draw2DRectangle(rect, titleBarColor, titleBarColor, c, c);*/
}
} // namespace gui
} // namespace awrts
