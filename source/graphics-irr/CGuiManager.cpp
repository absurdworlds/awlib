
#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/IGUIEnvironment.h>

#include "CInputManager.h"
#include "CGuiManager.h"

namespace hrengin {
namespace gui {

CGUIManager::CGUIManager(irr::gui::IGUIEnvironment* guienv,
irr::IrrlichtDevice* device)
: device_(device), guienv_(guienv)
{
	inputmgr_ = new io::CInputManager(device);
}

CGUIManager::~CGUIManager()
{

}

void CGUIManager::draw()
{
	guienv_->drawAll();
}

io::IInputManager* CGUIManager::getInputManager()
{
	return inputmgr_;
}
} // namespace gui
} // namespace hrengin
