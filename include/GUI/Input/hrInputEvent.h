
#ifndef __HG_hrInputEvent__
#define __HG_hrInputEvent__

#include <Base/hrTypes.h>

namespace hrengin
{
namespace gui
{

typedef void (*OnInputCallback)(u32 Event);

struct hrInputEvent
{
	OnInputCallback callback;
	u32				inputEvent;

	hrInputEvent(u32 pInputEvent, OnInputCallback pCallback) : callback(pCallback), inputEvent(pInputEvent) {}
};

} // namespace io
} // namespace hrengin

#endif//__HG_hrInputEvent__