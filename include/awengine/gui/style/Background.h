/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_Background_
#define _awrts_GUI_Background_
#include <string>

#include <awengine/graphics/Color.h>
#include <awengine/gui/style/Shared.h>

namespace awrts {
namespace gui {

class Background {
public:
	enum Style {
		None,
		Solid,
		Gradient,
		Image
	};

	virtual Background* none()
	{
		return nullptr;
	}
	virtual Background* solid()
	{
		return nullptr;
	}
	virtual Background* gradient()
	{
		return nullptr;
	}
	virtual Background* image()
	{
		return nullptr;
	}

	Style style()
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
	virtual Background* none()
	{
		return this;
	}
};

class BackgroundSolid : public Background {
public:
	BackgroundSolid(Style s, graphics::Color color)
		: Background(Background::Solid), c(color)
	{
	}
	graphics::Color color()
	{
		return c;
	}
	virtual Background* solid()
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
	graphics::Color color(Corner pos)
	{
		size_t tmp = size_t(pos);
		return tmp < 4 ? colors[tmp] : graphics::Color(0);
	}
	virtual Background* gradient()
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

	std::string path()
	{
		return img;
	}

	ImageRepeat repeat()
	{
		return tiling;
	}
	virtual Background* image()
	{
		return this;
	}
private:
	std::string img;
	ImageRepeat tiling;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_Background_
