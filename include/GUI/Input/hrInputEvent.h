
#ifndef __HG_hrInputEvent__
#define __HG_hrInputEvent__

#include <Base/hrTypes.h>

namespace hrengin
{
namespace gui
{

typedef void (*OnInputCallback)(u32 Event);
typedef void (*OnMouseEventCallback)(u32 Event, i32 X, i32 Y);

struct hrInputEvent
{
	union
	{
		OnInputCallback			OnInput;
		OnMouseEventCallback	OnMouseEvent;
	};
	
	u32	inputEvent;

	//hrInputEvent(u32 pInputEvent, OnInputCallback pCallback) : OnInput(pCallback), inputEvent(pInputEvent) {}
};

} // namespace io
} // namespace hrengin

#endif//__HG_hrInputEvent__