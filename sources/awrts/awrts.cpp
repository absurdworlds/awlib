
#define WIN32_LEAN_AND_MEAN
#include <hrEngin.h>
#pragma comment(lib, "hrEngin.lib")
#include <stdio.h>


int main()
{
	//hrengin::hriEncore* hrEngin = hrengin::KickstartEngine();
	bool b_runEngine = true;

	hrengin::graphics::hriVideoManager* videomgr = hrengin::graphics::GetManager();

	hrengin::graphics::hriVisNode* node = videomgr->CreateVisObject();
	hrengin::graphics::hriCameraNode* camera = videomgr->CreateCamera();
	camera->SetBehavior(hrengin::graphics::hriCameraNode::CAM_STRATEGIC);

	node->AddMesh("sotank.obj");
	//node->AddMesh("ground.obj");

	do
	{
		if(!videomgr->Draw())
		{
			b_runEngine = false;
		}
	}
	while(b_runEngine);

	//while (hrEngin->Roar());

	return 0;
}