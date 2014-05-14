
#ifndef __HG_hrEncore_h__
#define __HG_hrEncore_h__

namespace hrengin
{

/*
	Controls the spice, controls the universe.

	This class was used to run the program loop, but now it handles
	some of internal operations.

*/
class hriEncore
{
	public:
		virtual u32 GetTime() = 0;
		
		// Run the engine
		virtual bool Roar() = 0;
};

} // namespace hrengin

#endif//__HG_hrEncore_h__
