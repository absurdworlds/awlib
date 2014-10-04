/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IConsoleGUI_
#define _hrengin_IConsoleGUI_

#include <hrengin/common/types.h>

#include <hrengin/core/ILogger.h>

#include <hrengin/graphics/api.h>
#include <hrengin/gui/IUserInputReceiver.h>

namespace hrengin {
namespace core {
class IShell;
}
namespace gui {
class IGUIManager;

//! User interface console windows used to type commands
class IConsoleGUI : public IUserInputReceiver, public ILogBook {
public:
	virtual ~IConsoleGUI() {};
};

//! Creates a console window
HR_GRAPHICS_API IConsoleGUI* createConsole(core::IShell* shell, IGUIManager* guimgr);

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IConsoleGUI_
