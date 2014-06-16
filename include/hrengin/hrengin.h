#ifndef __H_INCLUDED__HRENGIN_hrengin
#define __H_INCLUDED__HRENGIN_hrengin

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrTypes.h>
#include <hrengin/base/IEncore.h>
#include <hrengin/base/ILogger.h>

#include <hrengin/entities/IEntityManager.h>
#include <hrengin/entities/IEventManager.h>

#include <hrengin/graphics/IVideoManager.h>
#include <hrengin/graphics/IVisNode.h>
#include <hrengin/graphics/ICameraNode.h>

#include <hrengin/gui/IGUIManager.h>
#include <hrengin/gui/input/IInputManager.h>

#include <hrengin/physics/IPhysicsManager.h>

#include <Windows.h>
namespace hrengin
{

/*Starters*/

//! Stattup all
HRENGIN_API IEncore* KickstartEngine ();

HRENGIN_API IEntityManager* GetManager ();
HRENGIN_API IEventManager* GetEventManager ();

HRENGIN_API HWND GetWindow ();

namespace graphics
{
HRENGIN_API IVideoManager* GetManager ();
}

namespace physics
{
HRENGIN_API IPhysicsManager* GetManager ();
} 

namespace gui
{
HRENGIN_API IGUIManager* GetManager ();

HRENGIN_API IInputManager* GetInputManager ();
}

} // namespace hrengin


#endif//__H_INCLUDED__HRENGIN_hrengin