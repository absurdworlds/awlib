/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include "CGUIListBox.h"

namespace hrengin {
namespace gui {

CGUIListBox::CGUIListBox()
{
}

CGUIListBox::~CGUIListBox()
{
}

u32 CGUIListBox::getId() const
{
	return 0;
}

u32 CGUIListBox::getParentId() const
{
	return 0;
}

u32 CGUIListBox::addItem(std::string text)
{
	return 0;
}

void CGUIListBox::adjustScrollPosition()
{
}


std::string CGUIListBox::getText() const
{
	return "";
}

void CGUIListBox::setText(std::string text)
{
}


} // namespace gui
} // namespace hrengin
