/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <memory>

#include <aw/platform/Window.h>

using namespace aw::platform;

int main()
{
	std::unique_ptr<Window> window;

Window* blyad = (Window::create());

	while (true);
}
