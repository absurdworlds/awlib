/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_Border_
#define _awrts_GUI_Border_
#include <string>

#include <awengine/common/types.h>
#include <awengine/graphics/Color.h>
#include <awengine/gui/style/Shared.h>

namespace awrts {
namespace gui {
class Border {
public:
	enum Style {
		None,
		Solid,
		Inward,
		Outward,
		Image
	};

	virtual Border* none()
	{
		return nullptr;
	}
	virtual Border* solid()
	{
		return nullptr;
	}
	virtual Border* inward()
	{
		return nullptr;
	}
	virtual Border* outward()
	{
		return nullptr;
	}
	virtual Border* image()
	{
		return nullptr;
	}

	Style style()
	{
		return s;
	}

protected:
	Border(Style s)
		: s(s)
	{
	}

	Style s;
};

class BorderNone : public Border {
public:
	BorderNone()
		: Border(Border::None)
	{
	}

	virtual Border* none()
	{
		return this;
	}
};

class BorderPlain : public Border {
protected:
	BorderPlain(u8 width, graphics::Color color, Border::Style s)
		: w(width), c(color), Border(s)
	{
	}
	u8 width()
	{
		return w;
	}
	graphics::Color color()
	{
		return c;
	}

private:
	//! Border width in pixels
	u8 w;
	graphics::Color c;

};

class BorderSolid : public BorderPlain {
public:
	BorderSolid(u8 width, graphics::Color color)
		: BorderPlain(width, color, Border::Solid)
	{
	}

	virtual Border* solid()
	{
		return this;
	}
};

class BorderInward : public BorderPlain {
public:
	BorderInward(u8 width, graphics::Color color)
		: BorderPlain(width, color, Border::Inward)
	{
	}

	virtual Border* inward()
	{
		return this;
	}
};

class BorderOutward : public BorderPlain {
public:
	BorderOutward(u8 width, graphics::Color color)
		: BorderPlain(width, color, Border::Outward)
	{
	}

	virtual Border* outward()
	{
		return this;
	}
};

class BorderImage : public Border {
public:
	BorderImage(std::string path,
	            u8 slice,
	            ImageRepeat mode = ImageRepeat::Tile)
		: img(path), mode(mode), Border(Border::Image)
	{
	}	
	std::string path()
	{
		return img;
	}

	u8 slice()
	{
		return width;
	}

	ImageRepeat repeat()
	{
		return mode;
	}

	virtual Border* image()
	{
		return this;
	}
private:
	std::string img;
	u8 width;
	ImageRepeat mode;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_Border_
