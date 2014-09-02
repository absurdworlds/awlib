
#include <Irrlicht/IGUIElement.h>

#include <hrengin/common/nowide.h>

#include "CGUIListBox.h"

namespace hrengin {
namespace gui {

CGUIListBox::CGUIListBox(irr::gui::IGUIElement* elem)
	: irrElement_(elem)
{
	elem->grab();
}

CGUIListBox::~CGUIListBox()
{
	irrElement_->drop();
}

u32 CGUIListBox::getId() const
{
	return irrElement_->getID();
}

u32 CGUIListBox::getParentId() const
{
	return irrElement_->getParent()->getID();
}

std::string CGUIListBox::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}

} // namespace gui
} // namespace hrengin
