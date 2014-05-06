
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
	node->AddMesh("sotank.obj");

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