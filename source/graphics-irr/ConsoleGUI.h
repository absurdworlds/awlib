/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CConsoleGUI_
#define _hrengin_CConsoleGUI_

#include <hrengin/gui/IGUIManager.h>
#include <hrengin/gui/IConsoleGUI.h>

namespace hrengin {
namespace gui {

class CConsoleGUI : public IConsoleGUI {
public:
	CConsoleGUI(core::IShell* shell, IGUIManager* guimgr);
	virtual ~CConsoleGUI();

	virtual bool onUserInput(gui::InputEvent input);
	virtual bool isEnabled();

	void log(std::string message);

private:
	core::IShell* shell_;
	IGUIWindow* window_;
	IGUITextBox* input_;
	IGUIListBox* output_;
};

} // namespace gui
} // namespace hrengin
#endif //_hrengin_CConsoleGUI_
