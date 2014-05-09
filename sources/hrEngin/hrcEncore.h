
#ifndef __HG_hrcEncore_h__
#define __HG_hrcEncore_h__

#include <hrEngin.h> 
#include "Graphics/hrcVideoManager.h" 
#include "PhysicsHavok/hrcHavokPhysics.h" 


namespace hrengin
{

//The main class. Controls the spice, controls the universe.
class hrcEncore : public hriEncore
{
	public:
		hrcEncore();
		virtual u32 GetTime();
		
		// Run the engine
		virtual bool Roar();
	protected:
		graphics::hrcVideoManager* VideoManager;
};

}

#endif//__HG_hrcEncore_h__