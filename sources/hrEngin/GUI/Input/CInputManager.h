
#ifndef __HG_CInputManager__
#define __HG_CInputManager__

#include <vector>

#include <Irrlicht/Irrlicht.h>

#include <hrengin/gui/input/IInputManager.h>

namespace hrengin
{
namespace gui
{

/*
	Class for handling user input. It inherits from irr::IEventReceiver
	so it can be passed into Irrlicht device as an user event receiver.
	Then it handles events through OnEvent() callback.

	It should be initialized after the video manager, although other
	order will work, because of checks for that case in either classes.

	Input manager may be not initialized at all, if not needed.
*/
class CInputManager : public IInputManager, public irr::IEventReceiver
{
	public:
		CInputManager();
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

#endif//__HG_CInputManager__