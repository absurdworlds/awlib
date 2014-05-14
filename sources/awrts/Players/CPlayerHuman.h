#ifndef __H_INCLUDED__AWRTS_CPlayerHuman
#define __H_INCLUDED__AWRTS_CPlayerHuman

#include <Base/hrVector3d.h>
#include <Base/Entities/hriInputReceiver.h>
#include <Graphics/Nodes/hriCameraNode.h>

#include "IPlayer.h"

namespace awrts
{

// human-controlled human

class CPlayerHuman : public IPlayer, public hrengin::hriInputReceiver
{
public:
	CPlayerHuman(hrengin::graphics::hriCameraNode* pPlayerCam);
	//void ApplyCamera();
	
	virtual bool ReceiveInput(hrengin::gui::hrInputEvent input)
	{
		return false;
	}

	virtual bool IsEnabled()
	{
		return !PlayerInputDisabled;
	}
	
	virtual bool Sync() 
	{
		//mPosition = mPOV->mPosition;
		return false;
	}
private:
	bool PlayerInputDisabled;

	//hrengin::Vector3d mPosition;

	hrengin::u32 mSlot;
	//hrengin::graphics::hriCameraNode* mDefaultPOV;
	hrengin::graphics::hriCameraNode* mPOV;
};

}

#endif//__H_INCLUDED__AWRTS_CPlayerHuman