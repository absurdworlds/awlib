
#include "CInputManager.h"

#include <Irrlicht/Irrlicht.h>

#include "../../Common/CInternalsManager.h"

namespace hrengin
{
namespace gui
{

CInputManager::CInputManager()
{
	if(__HRIM.videomgr)
	{
		__HRIM.videomgr->GetDevice()->setEventReceiver(this);
	}
}

bool CInputManager::OnEvent(const irr::SEvent& event)
{
	InputEvent inEvent = InputEvent();
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		inEvent.type = inEvent.INPUT_MOUSE_EVENT;

		switch(event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			inEvent.MouseInput.type = InputEvent::MINPUT_LMB_PRESSED;
			inEvent.MouseInput.X = event.MouseInput.X;
			inEvent.MouseInput.Y = event.MouseInput.Y;


	for(std::vector<IControllable*>::iterator it = mReceivers.begin(); it != mReceivers.end(); ++it)
	{
		if((*it)->IsEnabled())
		{
			(*it)->ReceiveInput(inEvent);
		}
	}
			break;
		default:
			inEvent.MouseInput.type = static_cast<InputEvent::MINPUT_TYPE>(999999);
			break;
		}
	}


	return false;
}


irr::gui::ICursorControl* CInputManager::GetCursorControl()
{
	return CursorControl;
}

bool CInputManager::RegisterReceiver(IControllable& receiver)
{
	mReceivers.push_back(&receiver);
	return true;
}

bool CInputManager::UnregisterReceiver(IControllable& receiver)
{
	//remove from mReceivers
	return true;
}

} // namespace io
} // namespace hrengin