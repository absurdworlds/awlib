
#ifndef __HG_hrcInputManager__
#define __HG_hrcInputManager__

#include <vector>

#include <Irrlicht/Irrlicht.h>

#include <GUI/Input/hriInputManager.h>

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
class hrcInputManager : public hriInputManager, public irr::IEventReceiver
{
	public:
		hrcInputManager();
		virtual bool RegisterReceiver(hriInputReceiver& receiver);		
		virtual bool UnregisterReceiver(hriInputReceiver& receiver);
	public:
		virtual irr::gui::ICursorControl* GetCursorControl();
		virtual bool OnEvent(const irr::SEvent& event);
	protected:
		irr::gui::ICursorControl* CursorControl;
		std::vector<hriInputReceiver*> mReceivers;
};


} // namespace io
} // namespace hrengin

#endif//__HG_hrcInputManager__