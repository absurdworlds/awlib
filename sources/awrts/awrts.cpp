
#include <stdio.h>

#include <string>
#include <hrengin/base/ILogger.h>
#include <hrengin/sound/ISoundManager.h>
#include <hrengin/gui/IInputManager.h>

#define WIN32_LEAN_AND_MEAN

//#include <Physics/IPhysicsPhantom.h>

#include "Players/CPlayerHuman.h"
#include "CApplication.h"
#include "CMapManager.h"
#include "Units/UnitType.h"
#include "Units/CUnitManager.h"

#include "awrts.h"

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
	//hrengin::IEncore* hrEngin = hrengin::KickstartEngine();
	bool runEngine = true;

	hrengin::sound::getSoundManager().initSounds();

	awrts::CApplication& app = awrts::CApplication::getInstance();

	hrengin::gui::IInputManager& inputmgr = hrengin::gui::getInputManager();
	//hrengin::graphics::ICameraNode* camera = videomgr->CreateCamera();
	awrts::CPlayerHuman* TestPlayer = new awrts::CPlayerHuman(app.videomgr.CreateCamera());
	inputmgr.RegisterReceiver(*TestPlayer);
	
	awrts::setupUnitTypes(app.unitmgr);

	app.mapmgr.loadMap("ground.obj");



	//hrengin::gui::IInputManager* InputMgr = hrengin::gui::GetInputManager();


	do
	{
		if(!app.videomgr.Draw())
		{
			runEngine = false;
		}
		
		if(!app.phymgr.step())
		{
			runEngine = false;
		}

		app.eventmgr.advance();
		
		app.entmgr.doSync();
		app.entmgr.doCleanup();

	}
	while(runEngine);

	//while (hrEngin->Roar());
	
	

	return 0;
}