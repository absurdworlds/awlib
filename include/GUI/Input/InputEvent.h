
#ifndef __HG_hrInputEvent__
#define __HG_hrInputEvent__

#include <Base/hrTypes.h>

namespace hrengin
{
namespace gui
{

/*
typedef void (*OnInputCallback)(u32 Event);
typedef void (*OnMouseEventCallback)(u32 Event, i32 X, i32 Y);
*/

struct InputEvent
{
	union
	{
		struct MouseInput
		{
			enum MINPUT_TYPE
			{
				MINPUT_LMB_PRESSED = 0,
				MINPUT_LMB_RELEASED,
				MINPUT_COUNT
			} type;

			//MINPUT_TYPE type;
			i32 X;
			i32 Y;
		} MouseInput;
	};
	
	enum INPUTEVENT_TYPE
	{
		INPUT_MOUSE_EVENT = 0,
		INPUT_EVENT_COUNT
	} type;

	//hrInputEvent(u32 pInputEvent, OnInputCallback pCallback) : OnInput(pCallback), inputEvent(pInputEvent) {}
};

} // namespace io
} // namespace hrengin

#endif//__HG_hrInputEvent__