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
private:
	core::IShell* shell_;
	IGUIWindow* window_;
	IGUITextBox* input_;
	IGUIListBox* output_;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_CConsoleGUI_
