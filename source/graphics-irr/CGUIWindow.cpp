
#include <Irrlicht/IGUIElement.h>

#include <hrengin/common/nowide.h>

#include "CGUIWindow.h"

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

std::string CGUIWindow::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}

void CGUIWindow::setText(std::string text)
{
	irrElement_->setText(locale::widen(text).c_str());
}


} // namespace gui
} // namespace hrengin
