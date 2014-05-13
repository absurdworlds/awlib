
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
	u32 temporary_budlocod;
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			temporary_budlocod = 1;
		}
	}

	
	for(std::vector<hrInputEvent>::iterator it = mEvents.begin(); it != mEvents.end(); ++it)
	{
		if((*it).inputEvent == temporary_budlocod)
		{
			(*it).OnMouseEvent(temporary_budlocod,event.MouseInput.X,event.MouseInput.Y);
		}
	}

	return false;
}


irr::gui::ICursorControl* hrcInputManager::GetCursorControl()
{
	return CursorControl;
}

u32 hrcInputManager::RegisterInputEvent(u32 Event, OnInputCallback callback)
{
	hrInputEvent event;
	event.OnInput = callback;
	event.inputEvent = Event;
	mEvents.push_back(event);
	return mEvents.size()-1;
}

u32 hrcInputManager::RegisterMouseEvent(u32 Event, OnMouseEventCallback callback)
{
	hrInputEvent event;
	event.OnMouseEvent = callback;
	event.inputEvent = Event;
	mEvents.push_back(event);
	return mEvents.size()-1;
}



} // namespace io
} // namespace hrengin