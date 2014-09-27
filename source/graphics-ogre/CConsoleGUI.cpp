/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <string>

#include <hrengin/core/IShell.h>
#include <hrengin/gui/IGUIWindow.h>
#include <hrengin/gui/IGUIListBox.h>
#include <hrengin/gui/IGUITextBox.h>
#include <hrengin/gui/Keycodes.h>
#include <hrengin/gui/IInputManager.h>

#include <hrengin/common/nowide.h>

#include "CConsoleGUI.h"

namespace hrengin {
namespace gui {

IConsoleGUI* createConsole(core::IShell* shell, IGUIManager* guimgr)
{
	return new CConsoleGUI(shell, guimgr);
}

CConsoleGUI::CConsoleGUI(core::IShell* shell, IGUIManager* guimgr)
	: shell_(shell)
{
}

CConsoleGUI::~CConsoleGUI()
{
	delete input_;
	delete output_;
	delete window_;
}

bool CConsoleGUI::onUserInput(gui::InputEvent input)
{
	return false;
}

bool CConsoleGUI::isEnabled()
{
	return true;
}

void CConsoleGUI::log(std::string message)
{
}

} // namespace gui
} // namespace hrengin
