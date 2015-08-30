/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <Irrlicht/IGUIElement.h>

#include <awrts/common/utf_convert.h>

#include "GUITextBox.h"

namespace awrts {
namespace gui {

GUITextBox::GUITextBox(irr::gui::IGUIElement* elem)
	: irrElement_(elem)
{
	elem->grab();
}

GUITextBox::~GUITextBox()
{
	irrElement_->drop();
}

u32 GUITextBox::getId() const
{
	return irrElement_->getID();
}

u32 GUITextBox::getParentId() const
{
	return irrElement_->getParent()->getID();
}

std::string GUITextBox::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}

void GUITextBox::setText(std::string text)
{
	irrElement_->setText(locale::widen(text).c_str());
}

} // namespace gui
} // namespace awrts
