/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <string>

#include <Irrlicht/IGUButton.h>
#include <Irrlicht/IGUWindow.h>
#include <Irrlicht/IGUEditBox.h>
#include <Irrlicht/IGUListBox.h>
#include <Irrlicht/IGUElement.h>
#include <Irrlicht/IGUScrollBar.h>

#include <aw/core/Shell.h>
#include <aw/gui/IGUWindow.h>
#include <aw/gui/IGUListBox.h>
#include <aw/gui/IGUTextBox.h>
#include <aw/gui/Keycodes.h>
#include <aw/gui/InputManager.h>

#include "ConsoleGUI.h"

namespace aw {
namespace gui {

ConsoleGUI_* createConsole(core::Shell* shell, GUIManager* guimgr)
{
	return new ConsoleGUI_(shell, guimgr);
}

ConsoleGUI_::ConsoleGUI_(core::Shell* shell, GUIManager* guimgr)
	: shell_(shell)
{
	// Ds are temporary — for testing while proper GUI event is not implemented
	window_ = guimgr->addWindow(Rect<i32>(10,10,500,300), false, L"Console",0,331);
	input_ = guimgr->addTextBox(Rect<i32>(5,260,480,280), L"", true,window_,332);
	output_ = guimgr->addListBox(Rect<i32>(5,20,480,250), true,window_,333);

	// again, temporary
	((irr::gui::IGUIWindow*)window_->getUnderlyingElement())->getCloseButton()->setVisible(false);
	((irr::gui::IGUIListBox*)output_->getUnderlyingElement())->setAutoScrollEnabled(true);

	guimgr->getInputManager()->registerReceiver(this);
}

ConsoleGUI_::~ConsoleGUI_()
{
	delete input_;
	delete output_;
	delete window_;
}

bool ConsoleGUI_::onUserInput(gui::InputEvent input)
{
	static bool prompt_active;
	switch(input.type) {
	case gui::InputEventType::GUEvent:
		switch(input.gui.event) {
		case gui::GUEventType::ElementHovered:
			break;
		case gui::GUEventType::ElementFocused:
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

bool ConsoleGUI_::isEnabled()
{
	return true;
}

void ConsoleGUI_::log(std::string message)
{
	output_->addItem(message);
	//TODO: cut the log when it becomes too long
}
} // namespace gui
} // namespace aw
