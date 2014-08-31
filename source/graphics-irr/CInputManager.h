#ifndef _hrengin_CInputManager_
#define _hrengin_CInputManager_

#include <vector>

#include <Irrlicht/Irrlicht.h>

#include <hrengin/gui/IInputManager.h>

namespace hrengin {
namespace io {

/*
	Class for handling user input. It inherits from irr::IEventReceiver
	so it can be passed into Irrlicht device as an user event receiver.
	Then it handles events through OnEvent() callback.

	To access user input, use IGUIManager::getInputManager()
 */
class CInputManager : public IInputManager, public irr::IEventReceiver {
public:
	CInputManager(irr::IrrlichtDevice* device);
	virtual bool RegisterReceiver(IControllable& receiver);
	virtual bool UnregisterReceiver(IControllable& receiver);
public:
	virtual irr::gui::ICursorControl* GetCursorControl();
	virtual bool OnEvent(const irr::SEvent& event);
protected:
	irr::gui::ICursorControl* CursorControl;
	std::vector<IControllable*> mReceivers;
};


} // namespace io
} // namespace hrengin

#endif//_hrengin_CInputManager_
