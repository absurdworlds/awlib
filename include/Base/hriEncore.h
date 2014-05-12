
#ifndef __HG_hrEncore_h__
#define __HG_hrEncore_h__

namespace hrengin
{

//The main class. Controls the spice, controls the universe.
class hriEncore
{
	public:
		virtual u32 GetTime() = 0;
		
		// Run the engine
		virtual bool Roar() = 0;
};

} // namespace hrengin

#endif//__HG_hrEncore_h__
