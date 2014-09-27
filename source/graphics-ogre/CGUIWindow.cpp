/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include "CGUIWindow.h"

namespace hrengin {
namespace gui {

CGUIWindow::CGUIWindow()
{
}

CGUIWindow::~CGUIWindow()
{
}

u32 CGUIWindow::getId() const
{
	return 0;
}

u32 CGUIWindow::getParentId() const
{
	return 0;
}

std::string CGUIWindow::getText() const
{
	return "";
}

void CGUIWindow::setText(std::string text)
{
}


} // namespace gui
} // namespace hrengin
