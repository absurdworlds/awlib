#ifndef __H_INCLUDED__AWRTS_IPlayer
#define __H_INCLUDED__AWRTS_IPlayer

//#include <Base/Entities/hriInputReceiver.h>
#include <Base/Entities/hriBaseEntity.h>

namespace awrts
{

// base player class

class IPlayer : public hrengin::hriBaseEntity
{
	virtual void OnParentRemove()
	{
		parent = 0;
	}
	
	
protected:
	virtual void EnterDeleteQueue() 
	{

	}
};

}

#endif//__H_INCLUDED__AWRTS_IPlayer