
#include "hrcInputManager.h"

#include <Irrlicht/Irrlicht.h>

#include "../../Internal/hrcInternalsManager.h"

namespace hrengin
{
namespace gui
{

hrcInputManager::hrcInputManager()
{
	if(__HRIM.videomgr)
	{
		__HRIM.videomgr->GetDevice()->setEventReceiver(this);
	}
}

bool hrcInputManager::OnEvent(const irr::SEvent& event)
{
	hrInputEvent inEvent;
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		inEvent.type = inEvent.INPUT_MOUSE_EVENT;

		switch(event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			inEvent.MouseInput.type = inEvent.MouseInput.MINPUT_LMB_PRESSED;
			break;
		default:
			break;
		}
	}

	
	for(std::vector<hriInputReceiver*>::iterator it = mReceivers.begin(); it != mReceivers.end(); ++it)
	{
		if((*it)->IsEnabled())
		{
			(*it)->ReceiveInput(inEvent);
		}
	}

	return false;
}


irr::gui::ICursorControl* hrcInputManager::GetCursorControl()
{
	return CursorControl;
}

bool hrcInputManager::RegisterReceiver(hriInputReceiver& receiver)
{
	mReceivers.push_back(&receiver);
	return true;
}

bool hrcInputManager::UnregisterReceiver(hriInputReceiver& receiver)
{
	//remove from mReceivers
	return true;
}

} // namespace io
} // namespace hrengin