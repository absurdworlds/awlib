
#ifndef __HG_hrEngin_h__
#define __HG_hrEngin_h__

#include "Base/Config/hrConfig.h" // the configuration file
#include "Base/hrTypes.h"
#include "Base/hriEncore.h"
#include "Base/hriEntityManager.h"
#include "Graphics/Base/hriVideoManager.h"
#include "GUI/Base/hriVideoManager.h"
#include "Physics/Base/hriPhysicsManager.h"

namespace hrengin
{

/*Starters*/

//! Stattup all
HRENGIN_API hriEncore* KickstartEngine ();

HRENGIN_API hriEntityManager* GetManager ();

namespace graphics
{
HRENGIN_API hriVideoManager* GetManager ();
}

namespace physics
{
HRENGIN_API hriPhysicsManager* GetManager ();
} 

namespace gui
{
HRENGIN_API hriGUIManager* Startup();
} 

} // namespace hrengin


#endif//__HG_hrEngin_h__