/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIManager_
#define _aw_GUIManager_

#include <aw/gui/GUIManager.h>

namespace irr {
class IrrlichtDevice;
namespace gui {
class GUIEnvironment;
}
}

namespace aw {
namespace gui {

class GUIManager : public GUIManager {
public:
	GUIManager(irr::gui::IGUIEnvironment* guienv,
	irr::IrrlichtDevice* device);
	virtual ~GUIManager();

	virtual void draw();

	virtual InputManager* getInputManager();

	virtual void setFont(std::string path);

	virtual GUIWindow* addWindow(Rect<i32> rect, bool isModal = false, 
		const wchar_t* title = 0, GUIElement* parent = 0, i32 id=-1);

	virtual GUITextBox* addTextBox(Rect<i32> rect, const wchar_t* text,
		bool border = true, GUIElement* parent = 0, i32 id = -1);

	virtual GUIListBox* addListBox(Rect<i32> rect, bool background = true,
		GUIElement* parent = 0, i32 id = -1);
private:
	irr::IrrlichtDevice* device_;
	irr::gui::IGUIEnvironment* guienv_;
	InputManager* inputmgr_;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUIManager_
