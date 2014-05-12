
#ifndef __HG_hrcInternalsManager__
#define __HG_hrcInternalsManager__

#include <Base/hrTypes.h>
#include "../GUI/Input/hrcInputManager.h"
#include "../Graphics/hrcVideoManager.h"
#include "../Physics/hrcBulletPhysics.h"

#include <Irrlicht.h>
/*
#if defined(_HR_PHYSICS_HAVOK)
	#include "../PhysicsHavok/hrcHavokPhysics.h"
	#define hrc__VARPhysics hrcHavokPhysics
#elif defined(_HR_PHYSICS_NEWTON) 
	#include "../PhysicsNewton/hrcNewtonPhysics.h"
	#define hrc__VARPhysics hrcNewtonPhysics
#endif*/

#define __HRIM hrengin::hrcInternalsManager::getInstance()

namespace hrengin
{
/* 
	The true master of this engine! Controls the spice, controls the universe.

	This class is used for internal access to all hrengin modules.
*/
class hrcInternalsManager
{
	public:
		static hrcInternalsManager& getInstance()
		{
			static hrcInternalsManager instance;
			return instance;
		}

		void Initialize()
		{
			if(!timer)
			{
				timer = videomgr->GetDevice()->getTimer();
			}
		}
		
		u32 GetTime()
		{
			return timer->getTime();
		}
		
	public: /* data */
		gui::hrcInputManager*		inputmgr;
		graphics::hrcVideoManager*	videomgr; 
		physics::hrcBulletPhysics*	physmgr;
		irr::ITimer*			timer;

	private:
		hrcInternalsManager() {};
		hrcInternalsManager(const hrcInternalsManager&);
		hrcInternalsManager& operator=(const hrcInternalsManager&);
};


} // namespace hrengin

#endif//__HG_hrcInternalsManager__