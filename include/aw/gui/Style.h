/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUI_Style_
#define _aw_GUI_Style_
#include <string>
#include <map>

#include <aw/gui/gui.h>
#include <aw/hdf/Value.h>

namespace aw {
namespace gui {
using hdf::Value;

class AW_GUI_EXP Style {
public:
	Style();
	virtual ~Style() = default;

	Value& property(std::string key)
	{
		return properties[key];
	}

	Style& substyle(std::string key)
	{
		return subclasses[key];
	}

	Style& operator[] (std::string key)
	{
		return substyle(key);
	}
private:
	std::map<std::string, Style> subclasses;
	std::map<std::string, Value> properties;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUI_Style_
