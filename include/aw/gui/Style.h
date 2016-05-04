/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_GUI_Style
#define aw_GUI_Style
#include <string>
#include <aw/types/types.h>

namespace aw {
namespace gui {
struct Style {
	enum ImageMode {
		Fixed,
		Tile,
		Stretch
	};

	struct Parameters {
		struct {
			u32 top, bottom;
			u32 left, right;
		} margin;

		struct {
			u32 top, bottom;
			u32 left, right;
		} padding;

		struct {
			std::string image;
			u32 color;
			u32 width;
			ImageMode mode;
		} border;

		struct {
			std::string image;
			u32 color;
			ImageMode mode;
		} background;

		struct {
			std::string family;
			std::string variant;
			u32 color;
			u32 size;
		} font;
	};

	Parameters& default_params()
	{
		return default_;
	}

	Parameters& state(std::string name)
	{
		auto found = states.find(name);

		if (found != std::end(states))
			return found->second;

		return default_;
	}

private:
	Parameters default_;
	std::map<std::string, Parameters> states;
};
} // namespace gui
} // namespace aw
#endif//aw_GUI_Style
