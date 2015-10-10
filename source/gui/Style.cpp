/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/gui/Style.h>
namespace awrts {
namespace gui {
void Style::initDefaults()
{
	ElementStyle windowStyle;

	windowStyle.setBorderStyle(std::make_unique<BorderOutward>(2,0xFFFFFFFF));
	windowStyle.setBackgroundStyle(std::make_unique<BackgroundGradient>(
	                  0xFF969696, 0xFF646464,
			  0xFF646464, 0xFF969696));
			
	properties["window"] = std::move(windowStyle);

	/*
	properties["border-color"] = hdf::Value(0xFFFFFFFF);
	properties["background-color"] = hdf::Value(0xFF969696);

	properties["window.border"] = hdf::Value("outset");
	properties["window.border-width"] = hdf::Value(2);
	properties["window.border-color"] = hdf::Value();

	properties["window.background"] = hdf::Value("gradient");
	properties["window.background-color-upper-left"] =
	       hdf::Value(0xFF969696);
	properties["window.background-color-upper-right"] =
	       hdf::Value(0xFF969696);
	properties["window.background-color-lower-left"] =
	       hdf::Value(0xFF646464);
	properties["window.background-color-lower-right"] =
	       hdf::Value(0xFF646464);

	properties["titlebar.background-color"] = hdf::Value(0xFF9696C8);*/
}
} // namespace gui
} // namespace awrts
