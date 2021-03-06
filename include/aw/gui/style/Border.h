/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_Border_
#define _aw_GUI_Border_
#include <string>

#include <aw/common/types.h>
#include <aw/graphics/Color.h>
#include <aw/gui/style/Shared.h>

namespace aw {
namespace gui {
class BorderNone;
class BorderPlain;
class BorderSolid;
class BorderInward;
class BorderOutward;
class BorderImage;

class Border {
public:
	enum Style {
		None,
		Solid,
		Inward,
		Outward,
		Image
	};

	virtual BorderNone* none()
	{
		return nullptr;
	}
	virtual BorderPlain* plain()
	{
		return nullptr;
	}
	virtual BorderSolid* solid()
	{
		return nullptr;
	}
	virtual BorderInward* inward()
	{
		return nullptr;
	}
	virtual BorderOutward* outward()
	{
		return nullptr;
	}
	virtual BorderImage* image()
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

	virtual BorderNone* none()
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

public:
	u8 width() const
	{
		return w;
	}

	graphics::Color color() const
	{
		return c;
	}

	virtual BorderPlain* plain()
	{
		return this;
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

	virtual BorderSolid* solid()
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

	virtual BorderInward* inward()
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

	virtual BorderOutward* outward()
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

	std::string path() const
	{
		return img;
	}

	u8 slice() const
	{
		return width;
	}

	ImageRepeat repeat() const
	{
		return mode;
	}

	virtual BorderImage* image()
	{
		return this;
	}
private:
	std::string img;
	u8 width;
	ImageRepeat mode;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUI_Border_
