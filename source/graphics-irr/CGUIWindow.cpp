
#include <Irrlicht/IGUIElement.h>

#include "CGUIWindow.h"

namespace irr {
namespace gui {
class IGUIElement;
}
}

namespace hrengin {
namespace gui {

CGUIWindow::CGUIWindow(irr::gui::IGUIElement* elem)
	: irrElement_(elem)
{
	elem->grab();
}

CGUIWindow::~CGUIWindow()
{
	irrElement_->drop();
}

u32 CGUIWindow::getId() const
{
	return irrElement_->getID();
}

u32 CGUIWindow::getParentId() const
{
	return irrElement_->getParent()->getID();
}


} // namespace gui
} // namespace hrengin
