
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "hrEngin.lib")

//#include <Physics/IPhysicsPhantom.h>

#include "Players/CPlayerHuman.h"
#include "CApplication.h"
#include "CMapManager.h"
#include "Units/UnitType.h"
#include "Units/CUnitManager.h"

#include "awrts.h"

namespace awrts
{
void setupUnitTypes(CUnitManager& unitmgr)
{
	awrts::CApplication& app = awrts::CApplication::getInstance();
	hrengin::u32 shape = app.phymgr->makeShape(hrengin::physics::IPhysicsManager::PHYS_SHAPE_SPHERE,5.);

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
	bool b_runEngine = true;
	
	awrts::CApplication& app = awrts::CApplication::getInstance();

	hrengin::gui::IInputManager* inputmgr = hrengin::gui::GetInputManager();
	//hrengin::graphics::ICameraNode* camera = videomgr->CreateCamera();
	awrts::CPlayerHuman* TestPlayer = new awrts::CPlayerHuman(app.videomgr->CreateCamera());
	inputmgr->RegisterReceiver(*TestPlayer);
	
	app.mapmgr->loadMap("ground.obj");

	awrts::setupUnitTypes(*app.unitmgr);

	app.unitmgr->createUnit('Stnk', hrengin::Vector3d(0,	0.635, 0));
	app.unitmgr->createUnit('Stnk', hrengin::Vector3d(10,	0.635, 0));
	app.unitmgr->createUnit('Stnk', hrengin::Vector3d(-10,	0.635, 0));
	app.unitmgr->createUnit('Btnk', hrengin::Vector3d(10 ,	0, -20), 135);
	app.unitmgr->createUnit('Btsp', hrengin::Vector3d(0  ,	0, -20), -135);
	app.unitmgr->createUnit('Btrk', hrengin::Vector3d(-5 ,	0, -30), -135);
	app.unitmgr->createUnit('Btsp', hrengin::Vector3d(-11,	0, -30), -135);

	//hrengin::gui::IInputManager* InputMgr = hrengin::gui::GetInputManager();

	do
	{
		if(!app.videomgr->Draw())
		{
			b_runEngine = false;
		}
		
		if(!app.phymgr->step())
		{
			b_runEngine = false;
		}
		
		app.entmgr->doSync();
		app.entmgr->doCleanup();

	}
	while(b_runEngine);

	//while (hrEngin->Roar());
	
	return 0;
}