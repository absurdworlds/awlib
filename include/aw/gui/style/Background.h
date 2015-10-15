/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_Background_
#define _aw_GUI_Background_
#include <string>

#include <aw/graphics/Color.h>
#include <aw/gui/style/Shared.h>

namespace aw {
namespace gui {
class BackgroundNone;
class BackgroundSolid;
class BackgroundGradient;
class BackgroundImage;

class Background {
public:
	enum Style {
		None,
		Solid,
		Gradient,
		Image
	};

	virtual BackgroundNone* none()
	{
		return nullptr;
	}
	virtual BackgroundSolid* solid()
	{
		return nullptr;
	}
	virtual BackgroundGradient* gradient()
	{
		return nullptr;
	}
	virtual BackgroundImage* image()
	{
		return nullptr;
	}

	Style style() const
	{
		return s;
	}
public:
	Background(Style style)
		: s(style)
	{
	}

private:

	Style s;
};

class BackgroundNone : public Background {
public:
	BackgroundNone()
		: Background(Background::None)
	{
	}

	virtual BackgroundNone* none()
	{
		return this;
	}
};

class BackgroundSolid : public Background {
public:
	BackgroundSolid(graphics::Color color)
		: Background(Background::Solid), c(color)
	{
	}

	graphics::Color color() const
	{
		return c;
	}
	virtual BackgroundSolid* solid()
	{
		return this;
	}
private:
	graphics::Color c;
};

class BackgroundGradient : public Background {
public:
	/*!
	 * Construct a Backfround Gradient with colors c1-c4.
	 * 
	 * Colors c1-c4 located in corners, starting from
	 * top left, and going counter-clockwise:
	 *
	 * c1 ----- c4  
	 *  |       |
	 * c2 ----- c3
	 */
	BackgroundGradient(
	           graphics::Color c1, graphics::Color c2,
	           graphics::Color c3, graphics::Color c4)
		: Background(Background::Gradient), colors({c1, c2, c3, c4})
	{
	}

	graphics::Color color(Corner pos) const
	{
		size_t tmp = size_t(pos);
		return tmp < 4 ? colors[tmp] : graphics::Color(0);
	}

	virtual BackgroundGradient* gradient()
	{
		return this;
	}
private:
	std::array<graphics::Color, 4> colors;
};

class BackgroundImage : public Background {
public:
	BackgroundImage(std::string path,
	                ImageRepeat tiling = ImageRepeat::Stretch)
		: Background(Background::Image), img(path), tiling(tiling)
	{
	}

	std::string path() const
	{
		return img;
	}

	ImageRepeat repeat() const
	{
		return tiling;
	}
	virtual BackgroundImage* image()
	{
		return this;
	}
private:
	std::string img;
	ImageRepeat tiling;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUI_Background_
