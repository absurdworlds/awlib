/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include "CGUITextBox.h"

namespace hrengin {
namespace gui {

CGUITextBox::CGUITextBox()
{
}

CGUITextBox::~CGUITextBox()
{
}

u32 CGUITextBox::getId() const
{
	return 0;
}

u32 CGUITextBox::getParentId() const
{
	return 0;
}

std::string CGUITextBox::getText() const
{
	return "";
}

void CGUITextBox::setText(std::string text)
{
}

} // namespace gui
} // namespace hrengin
