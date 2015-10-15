/*
 * Copyright (C) 2015  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_gui_button_
#define _awrts_gui_button_
#include <awengine/gui/Widget.h>

namespace awrts {
namespace gui {

//! Text box GUI element
class Button : public Widget {
public:
	virtual ~Button() = default;

	virtual bool isPressed();
private:
	bool state;
	void onPressed();
	void onReleased();
};

} // namespace gui
} // namespace awrts
#endif //_awrts_gui_button_
