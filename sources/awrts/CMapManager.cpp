
#include <hrengin/graphics/IVisNode.h>

#include "CApplication.h"
#include "CMapManager.h"
#include "Units/CUnitManager.h"

namespace awrts
{

bool CMapManager::loadMap(char * mapname)
{
	bool success = true;

	CApplication& app = CApplication::getInstance();
	
	hrengin::graphics::IVisNode* node = app.videomgr.CreateVisObject();
	node->AddMesh(mapname);
	
	app.unitmgr.createUnit('Stnk', hrengin::Vector3d(0,	0.635, 0));
	app.unitmgr.createUnit('Stnk', hrengin::Vector3d(10,	0.635, 0));
	app.unitmgr.createUnit('Stnk', hrengin::Vector3d(-10,	0.635, 0));
	app.unitmgr.createUnit('Btnk', hrengin::Vector3d(10 ,	0, -20), 135);
	app.unitmgr.createUnit('Btsp', hrengin::Vector3d(0  ,	0, -20), -135);
	app.unitmgr.createUnit('Btrk', hrengin::Vector3d(-5 ,	0, -30), -135);
	app.unitmgr.createUnit('Btsp', hrengin::Vector3d(-11,	0, -30), -135);

	return success;
}

}