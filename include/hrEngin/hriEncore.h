
#ifndef __HR_I_ENCORE__
#define __HR_I_ENCORE__

#include <hrtype.h>
#include <hriGraphicsCore.h>

namespace hrengin
{
class hriEncore
{
	public:
		virtual ~hriEncore() {}
		virtual uint32 GetTime() = 0;
		
		// Run the engine
		virtual bool Roar() = 0;

		virtual graphics::hriGraphicsCore* GetGCore() = 0;
	private:
};

} // namespace hrengin

#endif //__HR_I_ENCORE__