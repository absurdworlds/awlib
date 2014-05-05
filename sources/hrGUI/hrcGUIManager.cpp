
#include "hrcGUIManager.h"

namespace hrengin
{
namespace gui
{

	hrcGUIManager::hrcGUIManager(hriEncore* p)
		: parent(p)
	{		
		guienv = parent->GetGCore()->GetSceneManager()->getGUIEnvironment();
	#ifdef _DEBUG
		guienv->addStaticText(L"AWRTS_dev v. storm in a bottle (rev. 11)",irr::core::rect<irr::s32>(10,10,260,22), true);
	#endif //_DEBUG
	}

} // namespace gui
} // namespace hrengin