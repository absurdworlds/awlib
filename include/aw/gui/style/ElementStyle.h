/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_ElementStyle_
#define _aw_GUI_ElementStyle_
#include <string>
#include <map>
#include <memory>

#include <aw/gui/style/Border.h>
#include <aw/gui/style/Background.h>

namespace aw {
namespace gui {
class ElementStyle {
public:
	ElementStyle() = default;	
	~ElementStyle() = default;

	ElementStyle(ElementStyle&& other)
	{
		border = std::move(other.border);
		background = std::move(other.background);
	}

	ElementStyle& operator =(ElementStyle&& other)
	{
		border = std::move(other.border);
		background = std::move(other.background);
		return *this;
	}

	void setBorderStyle(std::unique_ptr<Border> newBorder)
	{
		border = std::move(newBorder);
	}

	void setBackgroundStyle(std::unique_ptr<Background> newBackground)
	{
		background = std::move(newBackground);
	}

	Border* getBorderStyle() const
	{
		return border.get();
	}

	Background* getBackgroundStyle() const
	{
		return background.get();
	}
private:
	std::unique_ptr<Border> border;
	std::unique_ptr<Background> background;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUI_ElementStyle_
