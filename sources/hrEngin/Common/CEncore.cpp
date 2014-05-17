
#include <Irrlicht/irrlicht.h>

#include "../Common/CInternalsManager.h"

#include "CEncore.h"

namespace hrengin
{

// Constructor: Initialize the engine
CEncore::CEncore()
{

}

u32 CEncore::GetTime()
{
	return __HRIM.GetTime();
}


bool CEncore::Roar()
{
	return false;
}


} // namespace hrengin