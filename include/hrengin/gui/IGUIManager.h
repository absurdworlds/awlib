/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IGUIManager_
#define _hrengin_IGUIManager_

#include <hrengin/common/Rect.h>

namespace hrengin {
namespace gui {
class IInputManager;
class IGUIElement;
class IGUIWindow;
class IGUITextBox;
class IGUIListBox;

//! Class for controling the GUI
class IGUIManager {
public:
	//! Virtual destructor
	virtual ~IGUIManager() {};

	/*! Draw all GUI
	   \note Should be drawn after everything else, or it will be overdrawn
	   or it may interfere with rendering (e.g. antialiasing)
	 */
	virtual void draw() = 0;

	//! Get the input manager \see IInputManager
	virtual IInputManager* getInputManager() = 0;

	//TODO: setFont(IFont font);
	//! Set main font
	virtual void setFont(std::string path) = 0;

	virtual IGUIWindow* addWindow(Rect<i32> rect, bool isModal = false, 
		const wchar_t* title = 0, IGUIElement* parent = 0,
		i32 id = -1) = 0;

	virtual IGUITextBox* addTextBox(Rect<i32> rect, const wchar_t* text,
		bool border = true, IGUIElement* parent = 0, i32 id = -1) = 0;

	virtual IGUIListBox* addListBox(Rect<i32> rect, bool background = true,
		IGUIElement* parent = 0, i32 id = -1) = 0;
		
	/*//! Create a Window GUI element
	virtual IGUIWindow* addWindow(IGUIElement* parent = 0,
		std::string name = "") = 0;
	//! Create a Text Box element
	virtual IGUITextBox* addTextBox(IGUIElement* parent = 0,
		std::string name = "") = 0;
	//! Create a List Box element
	virtual IGUIListBox* addListBox(IGUIElement* parent = 0,
		std::string name = "") = 0;*/
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIManager_
