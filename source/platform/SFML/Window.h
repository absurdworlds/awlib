/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Window_SFML_
#define _awrts_Window_SFML_
#include <SFML/Window.hpp>
#include <awengine/platform/Window.h>

namespace awrts {
namespace platform {
namespace sf_ {
/*
 * Implementation of platfrom::Window class as a wrapper
 * over SFML::Window.
 */
class Window : public platform::Window {
public:
	Window();
	virtual ~Window();

	virtual Vector2d<i32> getPosition();
	virtual Vector2d<u32> getSize();
	virtual void setSize(Vector2d<u32> const& dim);

	virtual bool isFocused() const;
	virtual void requestFocus();

	virtual void setTitle(std::string const& title);

	virtual void display();
private:
	sf::Window window;
};
} // namespace sf_
} // namespace platform
} // namespace awrts
#endif//_awrts_Window_SFML_
