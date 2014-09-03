#ifndef _hrengin_IConsoleGUI_
#define _hrengin_IConsoleGUI_

#include <hrengin/common/api.h>
#include <hrengin/common/types.h>
#include <hrengin/gui/IUserInputReceiver.h>
#include <hrengin/core/ILogger.h>

namespace hrengin {
namespace core {
class IShell;
}
namespace gui {
class IGUIManager;

class IConsoleGUI : public IUserInputReceiver, public ILogBook {
public:
	virtual ~IConsoleGUI() {};
};

HR_GRAPHICS_API IConsoleGUI* createConsole(core::IShell* shell, IGUIManager* guimgr);

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IConsoleGUI_
