
#ifndef __HG_CEncore_h__
#define __HG_CEncore_h__

#include <hrEngin.h> 
#include "../Graphics/CVideoManager.h" 
//#include "Physics/CBulletPhysics.h" 


namespace hrengin
{

/*
	The main class. Controls the spice, controls the universe.
	
*/
class CEncore : public IEncore
{
	public:
		CEncore();
		virtual u32 GetTime();
		
		// Run the engine
		virtual bool Roar();
	protected:
};

}

#endif//__HG_CEncore_h__