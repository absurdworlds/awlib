/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_Style_
#define _awrts_GUI_Style_
#include <string>
#include <map>

#include <awengine/gui/style/ElementStyle.h>

namespace awrts {
namespace gui {
class Style {
public:
	virtual ~Style() = default;

	void initDefaults();

	ElementStyle* getElementStyle(std::string element)
	{
		auto found = properties.find(element);

		if (found != properties.end()) {
			return &found->second;
		}

		return nullptr;
	}

	void setElementStyle(std::string element, ElementStyle style)
	{
		properties[element] = std::move(style);
	}
private:
	std::map<std::string, ElementStyle> properties;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_Style_
