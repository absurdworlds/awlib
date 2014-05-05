
#include "hrcEncore.h"
#include <hrGraphics.h>
#include <hrGUI.h>
#include "hrcUnitManager.h"

namespace hrengin
{

hrcEncore::hrcEncore()
{
	/*graphics::hGraphicsWrapper* hGraphicsWrapper;
	hGraphicsWrapper = graphics::Startup(graphics::GD_OPENGL, 800, 600, 32, false, false);*/
	GCore = graphics::Startup(this);
	GUIManager = gui::Startup(this);
	UnitManager = new hrcUnitManager(this);
	UnitManager->CreateUnit("blah");
}

uint32 hrcEncore::GetTime()
{
	return 0;
}

graphics::hriGraphicsCore* hrcEncore::GetGCore()
{
	return GCore;
}

bool hrcEncore::Roar()
{
	return GCore->Draw();
}

} // namespace hrengin
