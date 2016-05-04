/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_Stylesheet_
#define _aw_GUI_Stylesheet_
#include <string>
#include <map>

#include <aw/gui/gui.h>
#include <aw/gui/Style.h>

namespace aw {
namespace gui {
struct Stylesheet {
	~Stylesheet() = default;

	Style* lookup(std::string element)
	{
		auto found = styles.find(element);

		if (found != std::end(styles))
			return &found->second;

		return nullptr;
	}

	void set(std::string element, Style style)
	{
		styles[element] = std::move(style);
	}

private:
	using Key = std::string;

	std::map<Key, Style> styles;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUI_Stylesheet_
