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

void IrrSkin::drawCanvas(Rect<f32> const& rect)
{
}

void IrrSkin::draw3DBorderInset(Rect<f32> const& w)
{
	//Rect screen = /*wtf*/->getScreenDimensions();
	Vector2d<f32> screen(800,600);
	Rect<f32> rect;
	rect.upperLeft.x() = w.upperLeft.x() * screen.x();
	rect.upperLeft.y() = w.upperLeft.y() * screen.y();
	rect.lowerRight.x() = w.lowerRight.x() * screen.x();
	rect.lowerRight.y() = w.lowerRight.y() * screen.y();

	renderer.drawWindowBackground(toIrr(rect));
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


// for testing
// modified code from irr::CGUISkin
void IrrRenderer::drawWindowBackground(irr::core::rect<irr::s32> r)
{
	irr::core::rect<irr::s32> rect = r;
	std::cout << rect.LowerRightCorner.X << std::endl;
	std::cout << rect.LowerRightCorner.Y << std::endl;

	// top border
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + 1;
	Driver->draw2DRectangle(irr::video::SColor(255,255,255,255), rect);

	// left border
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	rect.LowerRightCorner.X = rect.UpperLeftCorner.X + 1;
	Driver->draw2DRectangle(irr::video::SColor(255,255,255,255), rect);

	// right border dark outer line
	rect.UpperLeftCorner.X = r.LowerRightCorner.X - 1;
	rect.LowerRightCorner.X = r.LowerRightCorner.X;
	rect.UpperLeftCorner.Y = r.UpperLeftCorner.Y;
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	Driver->draw2DRectangle(irr::video::SColor(255,50,50,50), rect);

	// right border bright innner line
	rect.UpperLeftCorner.X -= 1;
	rect.LowerRightCorner.X -= 1;
	rect.UpperLeftCorner.Y += 1;
	rect.LowerRightCorner.Y -= 1;
	Driver->draw2DRectangle(irr::video::SColor(255,130,130,130), rect);

	// bottom border dark outer line
	rect.UpperLeftCorner.X = r.UpperLeftCorner.X;
	rect.UpperLeftCorner.Y = r.LowerRightCorner.Y - 1;
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	rect.LowerRightCorner.X = r.LowerRightCorner.X;
	Driver->draw2DRectangle(irr::video::SColor(255,50,50,50), rect);

	// bottom border bright inner line
	rect.UpperLeftCorner.X += 1;
	rect.LowerRightCorner.X -= 1;
	rect.UpperLeftCorner.Y -= 1;
	rect.LowerRightCorner.Y -= 1;
	Driver->draw2DRectangle(irr::video::SColor(255,130,130,130), rect);

	// client area for background
	rect = r;
	rect.UpperLeftCorner.X +=1;
	rect.UpperLeftCorner.Y +=1;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y -= 2;

	const irr::video::SColor c1 = irr::video::SColor(255,100,100,100).getInterpolated ( 0xFFFFFFFF, 0.9f );
	const irr::video::SColor c2 = irr::video::SColor(255,150,150,150).getInterpolated ( 0xFFFFFFFF, 0.8f );

	Driver->draw2DRectangle(rect, c1, c1, c2, c2);
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
