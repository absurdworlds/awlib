/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <aw/io/InputCharStream.h>
#include <aw/gui/StyleLoader.h>

char const* test = "[window"
"[border width=1.0]"
"[background style=solid color=10324]"
"]";

int main()
{
	using namespace aw;
	io::InputCharStream stream(test);

	gui::StyleLoader loader;

	gui::Style style = loader.loadStyle(stream);

	std::cout << as_string(style["window"]["border"].property("width")) << std::endl;
	std::cout << as_string(style["window"]["background"].property("color")) << std::endl;
	std::cout << as_string(style["window"]["background"].property("style")) << std::endl;
}
