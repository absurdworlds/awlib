/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRAN.y, to the extent permitted by law.
 */
#include <Irrlicht/rect.h>
#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/IGUIEnvironment.h>
#include <Irrlicht/IGUIWindow.h>

#include <Irrlicht/IGUIFont.h>

#include <awrts/gui/GUIElement.h>

#include "InputManager.h"
#include "GuiManager.h"
#include "GUIWindow.h"
#include "GUITextBox.h"
#include "GUIListBox.h"

namespace awrts {
namespace gui {

GUIManager_::GUIManager_(irr::gui::IGUIEnvironment* guienv,
irr::IrrlichtDevice* device)
: device_(device), guienv_(guienv)
{
	inputmgr_ = new InputManager_(device);
}

GUIManager_::~GUIManager_()
{
}

void GUIManager_::draw()
{
	guienv_->drawAll();
}

InputManager* GUIManager_::getInputManager()
{
	return inputmgr_;
}

void GUIManager_::setFont(std::string path)
{
	irr::gui::IGUIFont* font = guienv_->getFont(path.c_str());
	if(font)
		guienv_->getSkin()->setFont(font);
}

inline irr::gui::IGUIElement* getUnderlyingElement(IGUIElement* e) {
	return static_cast<irr::gui::IGUIElement*>(e->getUnderlyingElement());
}

GUIWindow* GUIManager_::addWindow(Rect<i32> rect, bool isModal, 
	const wchar_t* title, GUIElement* parent, i32 id)
{
	irr::core::recti windowRect(rect.upperLeft.x, rect.upperLeft.y,
		rect.lowerRight.x, rect.lowerRight.y);

	irr::gui::IGUIElement* parentElem = 0;

	#if 0
	if(parent == 0) {
		parent = root_;
	}
	#endif
	if(parent != 0) {
		parentElem = getUnderlyingElement(parent);
	}

	irr::gui::IGUIElement* elem = guienv_->addWindow(windowRect,isModal,title,parentElem,id);

	return new GUIWindow_(elem);
}


GUITextBox* GUIManager_::addTextBox(Rect<i32> rect, const wchar_t* text,
	bool border, GUIElement* parent, i32 id)
{
	irr::core::recti elemRect(rect.upperLeft.x, rect.upperLeft.y,
		rect.lowerRight.x, rect.lowerRight.y);
	irr::gui::IGUIElement* parentElem = 0;

	if(parent != 0) {
		parentElem = getUnderlyingElement(parent);
	}

	irr::gui::IGUIElement* elem = guienv_->addEditBox(text,elemRect,border,parentElem,id);

	return new GUITextBox_(elem);
}

GUIListBox* GUIManager_::addListBox(Rect<i32> rect, bool background, GUIElement* parent, i32 id)
{
	irr::core::recti elemRect(rect.upperLeft.x, rect.upperLeft.y,
			rect.lowerRight.x, rect.lowerRight.y);
	irr::gui::IGUIElement* parentElem = 0;

	if(parent != 0) {
		parentElem = getUnderlyingElement(parent);
	}

	irr::gui::IGUIListBox* elem = guienv_->addListBox(elemRect,parentElem,id,background);

	return new GUIListBox_(elem);
}

} // namespace gui
} // namespace awrts
