
#define WIN32_LEAN_AND_MEAN
#include <hrEngin.h>
#pragma comment(lib, "hrEngin.lib")
#pragma comment(lib, "hrGraphics.lib")
#include <stdio.h>

int main()
{
	hrengin::hriEncore* hrEngin = hrengin::KickstartEngine();

	while (hrEngin->Roar());

	/*hGraphicsWrapper->CreateMesh("..\\data\\models\\sotmtank.obj", "..\\data\\materials\\sotank.tga", 0, 0, 0.635);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\sotmtank.obj", "..\\data\\materials\\sotank.tga", 0, -10, 0.635);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\sotmtank.obj", "..\\data\\materials\\sotank.tga", 0, 10, 0.635);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\ground.obj", "..\\data\\materials\\sotank.tga");
	hGraphicsWrapper->CreateMesh("..\\data\\models\\butank.obj", "..\\data\\materials\\default.tga",-20,10,0,135);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\butruck.obj", "..\\data\\materials\\default.tga",-20,0,0,180);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\butransport.obj", "..\\data\\materials\\default.tga",-30,-5,0,-135);
	hGraphicsWrapper->CreateMesh("..\\data\\models\\butransport.obj", "..\\data\\materials\\default.tga",-30,-11,0,-135);*/

	return 0;
}