
#ifndef __HR_C_ENCORE__
#define __HR_C_ENCORE__

#include <hriEncore.h>
#include <hriGraphicsCore.h>
#include <hriGUIManager.h>
#include <hriUnitManager.h>

namespace hrengin
{
class hrcEncore : public hriEncore
{
	public:
		hrcEncore();
		virtual ~hrcEncore() {};
		virtual uint32 GetTime();
		virtual graphics::hriGraphicsCore* GetGCore();

		// Run the engine
		virtual bool Roar();

	private:
		enum TimerSource
		{
			hets_null = 0,
			hets_graphics,
			hets_physics,
			hets_gui,
			hets_sound,
			hets_this,
			hets_count,
			hets_ = 0x7FFFFFFF //force 32 bit for byte-alignment
		} TimerSource;

		graphics::hriGraphicsCore*	GCore;
		gui::hriGUIManager*			GUIManager;

		hriUnitManager* UnitManager;

};

} // namespace hrengin

#endif // __HR_C_ENCORE__