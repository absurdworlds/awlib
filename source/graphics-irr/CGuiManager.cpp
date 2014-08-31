
#include <Irrlicht/IGUIEnvironment.h>

#include "CGuiManager.h"

namespace hrengin {
namespace graphics {
namespace gui {

void CGUIManager::draw()
{
	guienv_->drawAll();
}

} // namespace gui
} // namespace graphics
} // namespace hrengin
