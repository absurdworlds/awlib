/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <hrengin/gui/IGUIElement.h>

#include "CInputManager.h"
#include "CGuiManager.h"
#include "CGUIWindow.h"
#include "CGUITextBox.h"
#include "CGUIListBox.h"

namespace hrengin {
namespace gui {

CGUIManager::CGUIManager(Ogre::Root* ogreRoot, core::ISettingsManager* settings)
{
	inputmgr_ = new CInputManager(settings);
}

CGUIManager::~CGUIManager()
{
}

void CGUIManager::draw()
{
	guienv_->drawAll();
}

IInputManager* CGUIManager::getInputManager()
{
	return inputmgr_;
}


void CGUIManager::setFont(std::string path)
{
}

IGUIWindow* CGUIManager::addWindow(Rect<i32> rect, bool isModal, 
	const wchar_t* title, IGUIElement* parent, i32 id)
{
	return 0;
}


IGUITextBox* CGUIManager::addTextBox(Rect<i32> rect, const wchar_t* text,
	bool border, IGUIElement* parent, i32 id)
{
	return 0;
}

IGUIListBox* CGUIManager::addListBox(Rect<i32> rect, bool background, IGUIElement* parent, i32 id)
{
	return 0;
}

} // namespace gui
} // namespace hrengin
