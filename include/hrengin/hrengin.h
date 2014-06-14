#ifndef __H_INCLUDED__HRENGIN_hrengin
#define __H_INCLUDED__HRENGIN_hrengin

#include "Base/Config/hrConfig.h" // the configuration file
#include "Common/hrTypes.h"
#include "Base/IEncore.h"
#include "Base/IEntityManager.h"
//#include "entities/IEventManager.h"
#include <hrengin/entities/IEventManager.h>

/**/
#include "Graphics/Base/IVideoManager.h"
#include "Graphics/Nodes/IVisNode.h"
#include "Graphics/Nodes/ICameraNode.h"

#include "GUI/IGUIManager.h"
#include "GUI/Input/IInputManager.h"
#include "Physics/Base/IPhysicsManager.h"

namespace hrengin
{

/*Starters*/

//! Stattup all
HRENGIN_API IEncore* KickstartEngine ();

HRENGIN_API IEntityManager* GetManager ();
HRENGIN_API IEventManager* GetEventManager ();

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