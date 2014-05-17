
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "hrEngin.lib")

#include "Players/CPlayerHuman.h"
#include "CApplication.h"
#include "CMapManager.h"
#include "Units/CUnitType.h"
#include "Units/CUnitManager.h"

#include "awrts.h"

int main()
{
	//hrengin::IEncore* hrEngin = hrengin::KickstartEngine();
	bool b_runEngine = true;
	
	awrts::CApplication& app = awrts::CApplication::getInstance();

	//hrengin::graphics::ICameraNode* camera = videomgr->CreateCamera();
	awrts::IPlayer* TestPlayer = new awrts::CPlayerHuman(app.videomgr->CreateCamera());
	
	app.mapmgr->loadMap("ground.obj");

	awrts::CUnitType SOTank;	

	SOTank.mID = 'Stnk';
	SOTank.mVisualModelName = "sotank.obj";

	app.unitmgr->addType(SOTank);
	app.unitmgr->createUnit('Stnk');


	/*node->AddMesh("sotank.obj");
	node->SetPosition(hrengin::Vectorf3d(0, 0, 0.635));
	node->AddMesh("sotank.obj");
	node->SetPosition(hrengin::Vectorf3d(0, 10, 0.635));
	node->AddMesh("sotank.obj");	
	node->SetPosition(hrengin::Vectorf3d(0, -10, 0.635));
	node->AddMesh("butank.obj");
	node->SetPosition(hrengin::Vectorf3d(-20,10,0));
	node->SetRotation(hrengin::Vectorf3d(0,135,0));
	node->AddMesh("butruck.obj");
	node->SetPosition(hrengin::Vectorf3d(-20,0,0));
	node->SetRotation(hrengin::Vectorf3d(0,1180,0));
	node->AddMesh("butransport.obj");
	node->SetPosition(hrengin::Vectorf3d(-30,-5,0));
	node->SetRotation(hrengin::Vectorf3d(0,-135,0));
	node->AddMesh("butransport.obj");
	node->SetPosition(hrengin::Vectorf3d(-30,-11,0));
	node->SetRotation(hrengin::Vectorf3d(0,-135,0));*/

	//hrengin::gui::IInputManager* InputMgr = hrengin::gui::GetInputManager();

	do
	{
		if(!app.videomgr->Draw())
		{
			b_runEngine = false;
		}
		
		if(!app.phymgr->Step())
		{
			b_runEngine = false;
		}
	}
	while(b_runEngine);

	//while (hrEngin->Roar());
	
	return 0;
}