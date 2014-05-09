
#ifndef __HG_hrcHavokPhysics__
#define __HG_hrcHavokPhysics__

#include <Physics/Base/hriPhysicsManager.h>

/* Havok stuff */
#include <Common/Base/hkBase.h>	
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>

// Multithreading
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
//#include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Visual Debugge
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>

// Physics
#include <Physics/Dynamics/World/hkpWorld.h>

// Styuff
#include <Physics/Collide/Shape/Misc/PhantomCallback/hkpPhantomCallbackShape.h>
#include <Physics/Collide/Filter/Group/hkpGroupFilter.h>
/* ffuts kovaH */

#include <stdio.h>

namespace hrengin
{
namespace physics
{

class hrcHavokPhysics : public hriPhysicsManager
{
	public:
		hrcHavokPhysics();
		
		void Lock();
		void Unlock();

		bool Step();
		
		hkpRigidBody* CreateBox( hkReal X, hkReal Y, hkReal Z, hkReal mass = 10.0f, bool addToWorld = true, bool buulbultrah = false);
		hkpRigidBody* CreatePhantom( hkReal X, hkReal Y, hkReal Z);
		void InitThread();

	private:
		hkJobQueue* jobQueue;
		hkJobThreadPool* threadPool;
		hkMemoryRouter* memoryRouter;
		hkpGroupFilter* colFilter;

		hkpWorld* world;
		hkStopwatch stopWatch;
		hkReal lastStepTime;
		hkReal previousStepTime;

		// visual debugger
		// — aah, they've buggered me!
		// — hold on, I'll bring my debugger
		hkpPhysicsContext* vdbContext;
		hkVisualDebugger* visualDebugger;
		bool vdbActive;
		
		static void HK_CALL errorReport(const char* msg, void* userContext)
		{
			fprintf(stderr, "HAVOK©: \n" );
			fprintf(stderr,  msg );
			fprintf(stderr, "\n" );
		}

};

}	
} // namespace hrengin

#endif//__HG_hrcHavokPhysics__