/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Window_
#define _awrts_Window_
#include <awengine/common/types.h>
#include <awengine/utility/NonCopyable.h>

#include <awengine/math/Vector2d.h>

#include <awengine/platform/platform.h>

namespace awrts {
namespace platform {
/*!
 * Abstracts platform-specific windowing API.
 * Used as a target for rendering.
 */
class Window : NonCopyable {
public:
	virtual ~Window()
	{
	}

	/*!
	 * Get position of the window.
	 */
	virtual Vector2d<i32> getPosition() = 0;
	/*!
	 * Get size of the window canvas (render area).
	 */
	virtual Vector2d<u32> getSize() = 0;
	virtual void setSize(Vector2d<u32> const& dim) = 0;

	virtual bool isFocused() const = 0;
	virtual void requestFocus() = 0;

	virtual void setTitle(std::string const& title) = 0;

	virtual void display() = 0;

	static AW_SYS_EXP Window* create();
};
} // namespace platform
} // namespace awrts
#endif//_awrts_Window_
