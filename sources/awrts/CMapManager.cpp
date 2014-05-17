

#include "CApplication.h"
#include "CMapManager.h"

namespace awrts
{

bool CMapManager::loadMap(char * mapname)
{
	bool success = true;

	CApplication& app = CApplication::getInstance();
	
	hrengin::graphics::IVisNode* node = app.videomgr->CreateVisObject();
	node->AddMesh(mapname);

	return success;
}

}