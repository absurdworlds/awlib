
#ifndef __HG_CInternalsManager__
#define __HG_CInternalsManager__

#include <Irrlicht/Irrlicht.h>

#include <hrengin/common/hrTypes.h>

#include "../Common/CEncore.h"
#include "../Entities/CEntityManager.h"
#include "../GUI/Input/CInputManager.h"
#include "../Graphics/CVideoManager.h"
#include "../Physics/CBulletPhysics.h"

/*
#if defined(_HR_PHYSICS_HAVOK)
	#include "../PhysicsHavok/CHavokPhysics.h"
	#define C__VARPhysics CHavokPhysics
#elif defined(_HR_PHYSICS_NEWTON) 
	#include "../PhysicsNewton/CNewtonPhysics.h"
	#define C__VARPhysics CNewtonPhysics
#endif*/

#define __HRIM hrengin::CInternalsManager::getInstance()

namespace hrengin
{
/* 
	The true master of this engine! Controls the spice, controls the universe.

	This class is used for internal access to all hrengin modules.
*/
class CInternalsManager
{
	public:
		static CInternalsManager& getInstance()
		{
			static CInternalsManager instance;
			return instance;
		}

		/*void Initialize()
		{
			if(!timer)
			{
				timer = videomgr->GetDevice()->getTimer();
			}
		}*/
		
		u32 GetTime()
		{			
			static irr::ITimer* timer(videomgr->GetDevice()->getTimer());
			return timer->getTime();
		}
		
		u32 getTime()
		{			
			static irr::ITimer* timer(videomgr->GetDevice()->getTimer());
			return timer->getTime();
		}
		
	public: /* data */
		hrengin::CEncore*			encore;
		hrengin::CEntityManager*	entmgr;
		graphics::CVideoManager*	videomgr; 
		gui::CInputManager*			inputmgr;
		physics::CBulletPhysics*	physmgr;
		//irr::ITimer*				timer;

	private:
		CInternalsManager() {};
		CInternalsManager(const CInternalsManager&);
		CInternalsManager& operator=(const CInternalsManager&);
};


} // namespace hrengin

#endif//__HG_CInternalsManager__