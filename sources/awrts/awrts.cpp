
#define WIN32_LEAN_AND_MEAN
#include <hrEngin.h>
#pragma comment(lib, "hrEngin.lib")
#include <stdio.h>


int main()
{
	//hrengin::hriEncore* hrEngin = hrengin::KickstartEngine();
	bool b_runEngine = true;

	hrengin::graphics::hriVideoManager* videomgr = hrengin::graphics::GetManager();

	hrengin::graphics::hriCameraNode* camera = videomgr->CreateCamera();
	camera->SetBehavior(hrengin::graphics::hriCameraNode::CAM_STRATEGIC);
	videomgr->CreateLight();
	hrengin::physics::hriPhysicsManager* phymgr = hrengin::physics::GetManager ();
	
	hrengin::graphics::hriVisNode* node = videomgr->CreateVisObject();
	node->AddMesh("ground.obj");
	node->AddMesh("sotank.obj");
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
	node->SetRotation(hrengin::Vectorf3d(0,-135,0));

	do
	{
		if(!videomgr->Draw())
		{
			b_runEngine = false;
		}
		
		if(!phymgr->Step())
		{
			b_runEngine = false;
		}
	}
	while(b_runEngine);

	//while (hrEngin->Roar());

	return 0;
}