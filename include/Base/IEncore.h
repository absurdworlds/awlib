#ifndef __H_INCLUDED__HRENGIN_IEncore
#define __H_INCLUDED__HRENGIN_IEncore

namespace hrengin
{

/*
	Controls the spice, controls the universe.

	This class was used to run the program loop, but now it handles
	some of internal operations.

*/
class IEncore
{
	public:
		virtual u32 GetTime() = 0;
		
		// Run the engine
		virtual bool Roar() = 0;
};

} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IEncore
