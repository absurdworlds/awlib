
#ifndef __HG_hrcNewtonPhysics__
#define __HG_hrcNewtonPhysics__

#include <Physics/Base/hriPhysicsManager.h>

#include <stdio.h>

struct NewtonWorld;

namespace hrengin
{
namespace physics
{

class hrcNewtonPhysics : public hriPhysicsManager
{
	public:
		hrcNewtonPhysics();
		
		void Lock();
		void Unlock();

		bool Step();
	
		void InitThread();
	private:
		NewtonWorld* world;
		void* newtonDebugger;
		//SceneManager* sceneManager;
		
		u32 lastStepTime;
};

}	
} // namespace hrengin

#endif//__HG_hrcNewtonPhysics__