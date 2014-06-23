
#include <stdio.h>

#include <string>
#include <thread>
#include <hrengin/base/ILogger.h>
#include <hrengin/sound/ISoundManager.h>
#include <hrengin/gui/IInputManager.h>
#include <hrengin/common/hrengintime.h>

#define WIN32_LEAN_AND_MEAN

//#include <Physics/IPhysicsPhantom.h>

#include "Players/CPlayerHuman.h"
#include "CApplication.h"
#include "CMapManager.h"
#include "Units/UnitType.h"
#include "Units/CUnitManager.h"

#include "awrts.h"
#include <hrengin/base/ILogger.h>

namespace awrts {
void setupUnitTypes(CUnitManager& unitmgr)
{
	awrts::CApplication& app = awrts::CApplication::getInstance();
	hrengin::u32 shape = app.phymgr.makeShape(hrengin::physics::IPhysicsManager::PHYS_SHAPE_SPHERE,5.);

	awrts::UnitType SOTank;	
	SOTank.id = 'Stnk';
	SOTank.visualModelName = "sotank.obj";
	SOTank.guiSelectionShapeId = shape;
	
	awrts::UnitType BuTank;
	BuTank.id = 'Btnk';
	BuTank.visualModelName = "butank.obj";
	BuTank.guiSelectionShapeId = shape;

	awrts::UnitType BuTruck;
	BuTruck.id = 'Btrk';
	BuTruck.visualModelName = "butruck.obj";
	BuTruck.guiSelectionShapeId = shape;
		
	awrts::UnitType BuTransport;
	BuTransport.id = 'Btsp';
	BuTransport.visualModelName = "butransport.obj";
	BuTransport.guiSelectionShapeId = shape;
	
	unitmgr.addType(SOTank);
	unitmgr.addType(BuTank);
	unitmgr.addType(BuTruck);
	unitmgr.addType(BuTransport);
}
}

int main()
{
	awrts::CApplication& app = awrts::CApplication::getInstance();
	//hrengin::IEncore* hrEngin = hrengin::KickstartEngine();

	hrengin::sound::getSoundManager().initSounds();


	hrengin::gui::IInputManager& inputmgr = hrengin::gui::getInputManager();
	//hrengin::graphics::ICameraNode* camera = videomgr->CreateCamera();
	awrts::CPlayerHuman* TestPlayer = new awrts::CPlayerHuman(app.videomgr.CreateCamera());
	inputmgr.RegisterReceiver(*TestPlayer);
	
	awrts::setupUnitTypes(app.unitmgr);

	app.mapmgr.loadMap("ground.obj");


	hrengin::ILogger& logger = hrengin::getLogger();
	logger.init();
	TRACE("Starting up the engine")


	//hrengin::gui::IInputManager* InputMgr = hrengin::gui::GetInputManager();

	bool runEngine = true;

	hrengin::u32 time = hrengin::getTime();
	hrengin::u32 lastTime = time;
	hrengin::u32 cycles = 0;
	hrengin::u32 mean = 0;
	do
	{
		runEngine = app.videomgr.advance();

		if (!runEngine) break;

		lastTime = time;
		time = hrengin::getTime();
		
		if (app.profiling)
		{
			if (((cycles + 1) % 100) == 0) {
				hrengin::getLogger().push("DEBUG:");
				hrengin::getLogger().push(std::to_string(mean/100.0));
				hrengin::getLogger().push(hrengin::endl);
				mean = 0;
			} else {
				mean += time - lastTime;
			}
		}
		
		
		app.videomgr.draw();
		
		runEngine = app.phymgr.step();

		
		app.eventmgr.advance();

		app.entmgr.doSync();
		app.entmgr.doCleanup();
		cycles++;
	}
	while(runEngine);

	logger.stop();
	//while (hrEngin->Roar());
	
	

	return 0;
}