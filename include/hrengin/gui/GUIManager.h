/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_GUIManager_
#define _hrengin_GUIManager_

#include <hrengin/math/Rect.h>

namespace hrengin {
namespace gui {
class InputManager;
class GUIElement;
class GUIWindow;
class GUITextBox;
class GUIListBox;

//! Class for controling the GUI
class GUIManager {
public:
	//! Virtual destructor
	virtual ~GUIManager() {};

	/*! Draw all GUI
	   \note Should be drawn after everything else, or it will be overdrawn
	   or it may interfere with rendering (e.g. antialiasing)
	 */
	virtual void draw() = 0;

	//! Get the input manager \see InputManager
	virtual InputManager* getInputManager() = 0;

	//TODO: setFont(Font font);
	//! Set main font
	virtual void setFont(std::string path) = 0;

	virtual GUIWindow* addWindow(Rect<i32> rect, bool isModal = false, 
		const wchar_t* title = 0, GUIElement* parent = 0,
		i32 id = -1) = 0;

	virtual GUITextBox* addTextBox(Rect<i32> rect, const wchar_t* text,
		bool border = true, GUIElement* parent = 0, i32 id = -1) = 0;

	virtual GUIListBox* addListBox(Rect<i32> rect, bool background = true,
		GUIElement* parent = 0, i32 id = -1) = 0;

	/*//! Create a Window GUI element
	virtual GUIWindow* addWindow(IGUIElement* parent = 0,
		std::string name = "") = 0;
	//! Create a Text Box element
	virtual GUITextBox* addTextBox(IGUIElement* parent = 0,
		std::string name = "") = 0;
	//! Create a List Box element
	virtual GUIListBox* addListBox(IGUIElement* parent = 0,
		std::string name = "") = 0;*/
};

} // namespace gui
} // namespace hrengin
#endif //_hrengin_GUIManager_
