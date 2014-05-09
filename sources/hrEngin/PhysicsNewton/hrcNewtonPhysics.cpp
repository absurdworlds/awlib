
#include "../Internal/hrcInternalsManager.h"
#include "hrcNewtonPhysics.h"

#include "Newton/Newton.h"
#include "Newton/dVisualDebuggerServer/NewtonDebuggerServer.h"
//#include "Newton/NewtonClass.h"

static void ShutDown ();
static void* AllocMemory (int sizeInBytes);
static void FreeMemory (void *ptr, int sizeInBytes);

namespace hrengin
{
namespace physics
{	

hrcNewtonPhysics::hrcNewtonPhysics() 
{
	//sceneManager = new SceneManager();

	NewtonSetMemorySystem (AllocMemory, FreeMemory);

	world = NewtonCreate ();	

	//NewtonSetPlatformArchitecture (world, 0);

	// set a fix world size
//	dVector minSize (-500.0f, -500.0f, -500.0f);
//	dVector maxSize ( 500.0f,  500.0f,  500.0f);
//	NewtonSetWorldSize (g_world, &minSize[0], &maxSize[0]); 

}
	
void hrcNewtonPhysics::Lock()
{
}

void hrcNewtonPhysics::Unlock()
{	
}

void hrcNewtonPhysics::InitThread ()
{
}


bool hrcNewtonPhysics::Step ()
{
	int deltaTime;
	int physicLoopsTimeAcc;
	dFloat fps;
	dFloat physicTime;

	deltaTime = __HRIM.GetTime() - lastStepTime;
	lastStepTime = __HRIM.GetTime();
	//g_timeAccumulator += deltaTime;

	physicTime = 0;
	// advance the simulation at a fix step
	int loops = 0;
	physicLoopsTimeAcc = 0;


	// Process incoming events. 
	//ProcessEvents (world);
	
	// run the newton update function
	NewtonUpdate (world, 1.0f);
	
	NewtonDebuggerServe (newtonDebugger, 1.0f);


	return true;
}


}	
} // namespace hrengin
