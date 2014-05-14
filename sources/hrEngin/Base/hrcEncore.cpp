
#include <Irrlicht/irrlicht.h>

#include "../Internal/hrcInternalsManager.h"

#include "hrcEncore.h"

namespace hrengin
{

// Constructor: Initialize the engine
hrcEncore::hrcEncore()
{

}

u32 hrcEncore::GetTime()
{
	return __HRIM.GetTime();
}


bool hrcEncore::Roar()
{
	return false;
}


} // namespace hrengin