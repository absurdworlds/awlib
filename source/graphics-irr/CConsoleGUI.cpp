/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <string>

#include <Irrlicht/IGUIButton.h>
#include <Irrlicht/IGUIWindow.h>
#include <Irrlicht/IGUIEditBox.h>
#include <Irrlicht/IGUIListBox.h>
#include <Irrlicht/IGUIElement.h>
#include <Irrlicht/IGUIScrollBar.h>

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
	// IDs are temporary — for testing while proper GUI event is not implemented
	window_ = guimgr->addWindow(Rect<i32>(10,10,500,300), false, L"Console",0,331);
	input_ = guimgr->addTextBox(Rect<i32>(5,260,480,280), L"", true,window_,332);
	output_ = guimgr->addListBox(Rect<i32>(5,20,480,250), true,window_,333);

	// again, temporary
	((irr::gui::IGUIWindow*)window_->getUnderlyingElement())->getCloseButton()->setVisible(false);
	((irr::gui::IGUIListBox*)output_->getUnderlyingElement())->setAutoScrollEnabled(true);

	guimgr->getInputManager()->registerReceiver(this);
}

CConsoleGUI::~CConsoleGUI()
{
	delete input_;
	delete output_;
	delete window_;
}

bool CConsoleGUI::onUserInput(gui::InputEvent input)
{
	static bool prompt_active;
	switch(input.type) {
	case gui::InputEventType::GUIEvent:
		switch(input.gui.event) {
		case gui::GUIEventType::ElementHovered:
			break;
		case gui::GUIEventType::ElementFocused:
			break;
		}
		break;
	case gui::InputEventType::KeyboardEvent:
		if(input.key.keyCode == irr::KEY_RETURN && input.key.pressedDown == true) {
			std::string inputStr = input_->getText();
			input_->setText("");
			shell_->execute(inputStr);
		}
		break;
	}

	return false;
}

bool CConsoleGUI::isEnabled()
{
	return true;
}

void CConsoleGUI::log(std::string message)
{
	output_->addItem(message);
	//TODO: cut the log when it becomes too long
}

} // namespace gui
} // namespace hrengin
