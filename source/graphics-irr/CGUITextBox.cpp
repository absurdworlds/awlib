
#include <Irrlicht/IGUIElement.h>

#include <hrengin/common/nowide.h>

#include "CGUITextBox.h"

namespace hrengin {
namespace gui {

CGUITextBox::CGUITextBox(irr::gui::IGUIElement* elem)
	: irrElement_(elem)
{
	elem->grab();
}

CGUITextBox::~CGUITextBox()
{
	irrElement_->drop();
}

u32 CGUITextBox::getId() const
{
	return irrElement_->getID();
}

u32 CGUITextBox::getParentId() const
{
	return irrElement_->getParent()->getID();
}

std::string CGUITextBox::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}


} // namespace gui
} // namespace hrengin
