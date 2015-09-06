/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_visitor_
#define _awrts_gui_visitor_
#include <awengine/gui/Canvas.h>
#include <awengine/gui/Widget.h>
#include <awengine/gui/Drawer.h>
#include "IrrSkin.h"

namespace awrts {
namespace gui {

virtual IrrSkin::~IrrSkin();

void IrrSkin::drawCanvas(Rect<f32> rect)
{

}

void IrrSkin::drawWindowBackground(Rect<f32> w)
{
	Rect screen = /*wtf*/->getScreenDimensions();
	Rect rect;
	rect.upperLeft.x() = w.upperLeft.x() * screen.upperLeft.x();
	rect.upperLeft.y() = w.upperLeft.y() * screen.upperLeft.y();
	rect.lowerRight.x() = w.lowerRight.x() * screen.lowerRight.x();
	rect.lowerRight.y() = w.lowerRight.y() * screen.lowerRight.y();

	renderer->drawWindowBackgroundIrr(toIrr(rect));
}

} // namespace gui
} // namespace awrts

namespace irr {
// for testing
// modified code from irr::CGUISkin
void IrrRenderer::drawWindowBackgroundIrr(irr::core::rect<s32> r)
{
	irr::core::rect<s32> rect = r;

	// top border
	rect.LowerRightCorner.Y = rect.UpperLeftCorner.Y + 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_HIGH_LIGHT), rect, clip);

	// left border
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	rect.LowerRightCorner.X = rect.UpperLeftCorner.X + 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_HIGH_LIGHT), rect, clip);

	// right border dark outer line
	rect.UpperLeftCorner.X = r.LowerRightCorner.X - 1;
	rect.LowerRightCorner.X = r.LowerRightCorner.X;
	rect.UpperLeftCorner.Y = r.UpperLeftCorner.Y;
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	Driver->draw2DRectangle(getColor(EGDC_3D_DARK_SHADOW), rect, clip);

	// right border bright innner line
	rect.UpperLeftCorner.X -= 1;
	rect.LowerRightCorner.X -= 1;
	rect.UpperLeftCorner.Y += 1;
	rect.LowerRightCorner.Y -= 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_SHADOW), rect, clip);

	// bottom border dark outer line
	rect.UpperLeftCorner.X = r.UpperLeftCorner.X;
	rect.UpperLeftCorner.Y = r.LowerRightCorner.Y - 1;
	rect.LowerRightCorner.Y = r.LowerRightCorner.Y;
	rect.LowerRightCorner.X = r.LowerRightCorner.X;
	Driver->draw2DRectangle(getColor(EGDC_3D_DARK_SHADOW), rect, clip);

	// bottom border bright inner line
	rect.UpperLeftCorner.X += 1;
	rect.LowerRightCorner.X -= 1;
	rect.UpperLeftCorner.Y -= 1;
	rect.LowerRightCorner.Y -= 1;
	Driver->draw2DRectangle(getColor(EGDC_3D_SHADOW), rect, clip);

	// client area for background
	rect = r;
	rect.UpperLeftCorner.X +=1;
	rect.UpperLeftCorner.Y +=1;
	rect.LowerRightCorner.X -= 2;
	rect.LowerRightCorner.Y -= 2;

	const video::SColor c1 = getColor(EGDC_WINDOW).getInterpolated ( 0xFFFFFFFF, 0.9f );
	const video::SColor c2 = getColor(EGDC_WINDOW).getInterpolated ( 0xFFFFFFFF, 0.8f );

	Driver->draw2DRectangle(rect, c1, c1, c2, c2, clip);
}
}
#endif //_awrts_gui_visitor_
