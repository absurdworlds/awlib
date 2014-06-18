
#ifndef __HG_CEncore_h__
#define __HG_CEncore_h__

#include <hrengin/base/IEncore.h>
#include <hrengin/common/hrengintime.h>

namespace hrengin
{

/*
	The main class. Controls the spice, controls the universe.
	
*/
class CEncore : public IEncore
{
	public:
		CEncore();
		virtual u32 getTime();
		
		// Run the engine
		virtual bool Roar();
	protected:
};

}

#endif//__HG_CEncore_h__