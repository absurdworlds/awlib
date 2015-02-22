/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ConsoleGUI_
#define _hrengin_ConsoleGUI_

#include <hrengin/gui/IGUManager.h>
#include <hrengin/gui/ConsoleGUI.h>

namespace hrengin {
namespace gui {

class ConsoleGUI : public ConsoleGUI {
public:
	ConsoleGUI(core::Shell* shell, IGUManager* guimgr);
	virtual ~ConsoleGUI();

	virtual bool onUserInput(gui::InputEvent input);
	virtual bool isEnabled();

	void log(std::string message);

private:
	core::Shell* shell_;
	IGUWindow* window_;
	IGUTextBox* input_;
	IGUListBox* output_;
};

} // namespace gui
} // namespace hrengin
#endif //_hrengin_ConsoleGUI_
