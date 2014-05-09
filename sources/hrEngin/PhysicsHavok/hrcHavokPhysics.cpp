
#include "hrcHavokPhysics.h"

// Physics
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
//#include <Common/Base/Fwd/hkcstdio.h>

#include <Common/Base/System/Io/IStream/hkIStream.h>	//loadFileStream from tutor of shapeloader
#include <Common/Serialize/Util/hkSerializeUtil.h>	// Serialize, error details
#include <Common/Serialize/Util/hkRootLevelContainer.h>	//serialize
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>	//also serialize, comracs idea
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>	//collision agents registrator

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>


namespace hrengin
{
namespace physics
{	

hrcHavokPhysics::hrcHavokPhysics() 
	: lastStepTime(0), previousStepTime(0)
{
	memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo( 500* 1024 ) );
	hkBaseSystem::init( memoryRouter, errorReport );

	{
		hkHardwareInfo hwInfo;
		hkGetHardwareInfo(hwInfo);

		hkCpuJobThreadPoolCinfo threadPoolCinfo;
		threadPoolCinfo.m_numThreads = hwInfo.m_numThreads - 1;
		
		threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
		threadPool = new hkCpuJobThreadPool( threadPoolCinfo );

		hkJobQueueCinfo info;
		info.m_jobQueueHwSetup.m_numCpuThreads = hwInfo.m_numThreads;//totalNumThreadsUsed;
		jobQueue = new hkJobQueue(info);
	}

	hkMonitorStream::getInstance().resize(200000);

	{
		hkpWorldCinfo worldInfo; 
		worldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;		
		worldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_FIX_ENTITY;

		world = new hkpWorld(worldInfo); 


		world->lock(); 

		hkpAgentRegisterUtil::registerAllAgents( world->getCollisionDispatcher() );
		world->registerWithJobQueue( jobQueue ); 

		world->unlock();
	}

	{ 
		hkArray<hkProcessContext*> contexts;

		vdbContext = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses(); 
		vdbContext->addWorld(world); 
		contexts.pushBack(vdbContext);

		visualDebugger = new hkVisualDebugger(contexts);
		visualDebugger->serve();
		vdbActive = true;
	} 
	
	{
		world->lock(); 

		colFilter = new hkpGroupFilter();
		colFilter->disableCollisionsUsingBitfield(0xffffffff, 0xffffffff );
		colFilter->enableCollisionsUsingBitfield( 1U		, 0x00000080 );	 // COLGROUP_NOCOLLIDE
		colFilter->enableCollisionsUsingBitfield( 1U << 1	, 0xffffff56 );	 // COLGROUP_WORLD
		colFilter->enableCollisionsUsingBitfield( 1U << 2	, 0xffffff36 );  // COLGROUP_BASE
		colFilter->enableCollisionsUsingBitfield( 1U << 3	, 0xffffff00 );  // COLGROUP_NOCOLLIDE_INTERNAL
		colFilter->enableCollisionsUsingBitfield( 1U << 4	, 0x000000f6 );  // COLGROUP_NOCOLLIDE_CUSTOM
		colFilter->enableCollisionsUsingBitfield( 1U << 5	, 0xfffffff2 );  // COLGROUP_NOCOLLIDE_WORLD
		colFilter->enableCollisionsUsingBitfield( 1U << 6	, 0xfffffff4 );  // COLGROUP_NOCOLLIDE_BASE
		colFilter->enableCollisionsUsingBitfield( 1U << 7	, 0xfffffff1 );  // COLGROUP_COLLIDE_NOCOLLIDE
		world->setCollisionFilter( colFilter );


		world->unlock();
	}

	{ 
		stopWatch.start();
	}
}
	
void hrcHavokPhysics::Lock()
{
	world->lock(); 
}

void hrcHavokPhysics::Unlock()
{	
	world->unlock();
}

void hrcHavokPhysics::InitThread ()
{
	hkBaseSystem::initThread(memoryRouter);
}


bool hrcHavokPhysics::Step ()
{
	//world->lock();
	hkReal Elapsed = stopWatch.getElapsedSeconds(); 
	hkReal StepTime = Elapsed - lastStepTime; 

	if(StepTime >= 4.0f)
	{
		previousStepTime = lastStepTime;
		lastStepTime = Elapsed;

		hkpStepResult stepResult = world->stepMultithreaded( jobQueue, threadPool, StepTime );

		if(stepResult == HK_STEP_RESULT_SUCCESS)
		{
			if( vdbActive )
			{
				vdbContext->syncTimers( threadPool );
				visualDebugger->step();
			}

			hkMonitorStream::getInstance().reset();
			threadPool->clearTimerData();

			//world->unlock();
		
			return true;
		}
		else
		{
			return false;
		}
	}
}

hkpRigidBody* hrcHavokPhysics::CreatePhantom( hkReal X, hkReal Y, hkReal Z)
{
	/*static int caropaks = 0;
	hkpBoxShape* boxShape = new hkpBoxShape( hkVector4(X, Y, Z) ); 

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_shape = boxShape;

	if(buulbultrah == true)
	{
	//	bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
	}

	hkpMassProperties massProperties; 
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, mass, massProperties);

	bodyCinfo.setMassProperties(massProperties);

	hkpRigidBody* rigidBody = new hkpRigidBody(bodyCinfo); 
	rigidBody->setPosition( hkVector4( 0, 4.0f*caropaks, 0 ) );
	boxShape->removeReference();
	
	//Lock();	
	if(addToWorld) world->addEntity(rigidBody);
	//Unlock();	
	caropaks++;
	return rigidBody;*/
}
		
hkpRigidBody* hrcHavokPhysics::CreateBox( hkReal X, hkReal Y, hkReal Z, hkReal mass, bool addToWorld, bool buulbultrah)
{
	static int caropaks = 0;
	hkpBoxShape* boxShape = new hkpBoxShape( hkVector4(X, Y, Z) ); 

	hkpRigidBodyCinfo bodyCinfo;
	bodyCinfo.m_shape = boxShape;

	if(buulbultrah == true)
	{
	//	bodyCinfo.m_motionType = hkpMotion::MOTION_FIXED;
	}

	hkpMassProperties massProperties; 
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, mass, massProperties);

	bodyCinfo.setMassProperties(massProperties);

	hkpRigidBody* rigidBody = new hkpRigidBody(bodyCinfo); 
	rigidBody->setPosition( hkVector4( 0, 4.0f*caropaks, 0 ) );
	boxShape->removeReference();
	
	//Lock();	
	if(addToWorld) world->addEntity(rigidBody);
	//Unlock();	
	caropaks++;
	return rigidBody;
}


}	
} // namespace hrengin
