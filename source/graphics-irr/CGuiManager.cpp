
#include <Irrlicht/rect.h>
#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/IGUIEnvironment.h>
#include <Irrlicht/IGUIWindow.h>

#include <Irrlicht/IGUIFont.h>

#include <hrengin/gui/IGUIElement.h>

#include "CInputManager.h"
#include "CGuiManager.h"
#include "CGUIWindow.h"
#include "CGUITextBox.h"
#include "CGUIListBox.h"

namespace hrengin {
namespace gui {

CGUIManager::CGUIManager(irr::gui::IGUIEnvironment* guienv,
irr::IrrlichtDevice* device)
: device_(device), guienv_(guienv)
{
	inputmgr_ = new CInputManager(device);
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
	irr::gui::IGUIFont* font = guienv_->getFont(path.c_str());
	if(font) {
		guienv_->getSkin()->setFont(font);
	}
}

inline irr::gui::IGUIElement* getUnderlyingElement(IGUIElement* e) {
	return static_cast<irr::gui::IGUIElement*>(e->getUnderlyingElement());
}

IGUIWindow* CGUIManager::addWindow(Rect<i32> rect, bool isModal, 
	const wchar_t* title, IGUIElement* parent, i32 id)
{
	irr::core::recti windowRect(rect.upperLeft_.X, rect.upperLeft_.Y, rect.lowerRight_.X, rect.lowerRight_.Y);
	
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

	//

	return new CGUIWindow(elem);
}


IGUITextBox* CGUIManager::addTextBox(Rect<i32> rect, const wchar_t* text,
	bool border, IGUIElement* parent, i32 id)
{
	irr::core::recti elemRect(rect.upperLeft_.X, rect.upperLeft_.Y, rect.lowerRight_.X, rect.lowerRight_.Y);
	irr::gui::IGUIElement* parentElem = 0;
	
	#if 0
	if(parent == 0) {
		parent = root_;
	}
	#endif
	if(parent != 0) {
		parentElem = getUnderlyingElement(parent);
	}
	
	irr::gui::IGUIElement* elem = guienv_->addEditBox(text,elemRect,border,parentElem,id);

	return new CGUITextBox(elem);
}

IGUIListBox* CGUIManager::addListBox(Rect<i32> rect, bool background, IGUIElement* parent, i32 id)
{
	irr::core::recti elemRect(rect.upperLeft_.X, rect.upperLeft_.Y, rect.lowerRight_.X, rect.lowerRight_.Y);
	irr::gui::IGUIElement* parentElem = 0;
	
	#if 0
	if(parent == 0) {
		parent = root_;
	}
	#endif
	if(parent != 0) {
		parentElem = getUnderlyingElement(parent);
	}
	
	irr::gui::IGUIListBox* elem = guienv_->addListBox(elemRect,parentElem,id,background);

	return new CGUIListBox(elem);
}

} // namespace gui
} // namespace hrengin
