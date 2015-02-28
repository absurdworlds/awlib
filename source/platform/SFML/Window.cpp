/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "Window.h"

namespace hrengin {
namespace platform {
// TODO: move this into generic/Window.cpp
Window* Window::create()
{
	return new sf_::Window();
}

namespace sf_ {
Window::Window()
	: window(sf::VideoMode(800, 600), "Untitled window")
{
}

Window::~Window()
{
	window.close();
}

Vector2d<i32> Window::getPosition()
{
	return Vector2d<i32>();
}

Vector2d<u32> Window::getSize()
{
	return Vector2d<u32>();
}

bool Window::isFocused() const
{
	return window.hasFocus();
}

void Window::requestFocus()
{
}

void Window::display()
{
	window.display();
}

void Window::setSize(Vector2d<u32> const& dim)
{
}

void Window::setTitle(std::string const& title)
{
}
} // namespace sf_
} // namespace platform
} // namespace hrengin
