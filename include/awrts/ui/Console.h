/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ConsoleGUI_
#define _aw_ConsoleGUI_

#include <aw/common/types.h>

#include <aw/core/Logger.h>

#include <aw/gui/gui.h>
#include <aw/gui/UserInputReceiver.h>

namespace aw {
namespace core {
class Shell;
}
namespace gui {
class GUIManager;

//! User interface console windows used to type commands
class ConsoleGUI : public UserInputReceiver, public core::LogBook {
public:
	virtual ~ConsoleGUI() {};
};

//! Creates a console window
HR_GUI_EXP ConsoleGUI* createConsole(core::Shell* shell, GUIManager* guimgr);

} // namespace gui
} // namespace aw
#endif //_aw_ConsoleGUI_
