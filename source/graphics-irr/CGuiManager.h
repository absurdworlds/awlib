/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CGUIManager_
#define _hrengin_CGUIManager_

#include <hrengin/gui/IGUIManager.h>

namespace irr {
class IrrlichtDevice;
namespace gui {
class IGUIEnvironment;
}
}

namespace hrengin {
namespace gui {

class CGUIManager : public IGUIManager {
public:
	CGUIManager(irr::gui::IGUIEnvironment* guienv,
	irr::IrrlichtDevice* device);
	virtual ~CGUIManager();

	virtual void draw();

	virtual IInputManager* getInputManager();

	virtual void setFont(std::string path);

	virtual IGUIWindow* addWindow(Rect<i32> rect, bool isModal = false, 
		const wchar_t* title = 0, IGUIElement* parent = 0, i32 id=-1);

	virtual IGUITextBox* addTextBox(Rect<i32> rect, const wchar_t* text,
		bool border = true, IGUIElement* parent = 0, i32 id = -1);

	virtual IGUIListBox* addListBox(Rect<i32> rect, bool background = true,
		IGUIElement* parent = 0, i32 id = -1);
private:
	irr::IrrlichtDevice* device_;
	irr::gui::IGUIEnvironment* guienv_;
	IInputManager* inputmgr_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CGUIManager_
