#ifndef __H_INCLUDED__AWRTS_CPlayerHuman
#define __H_INCLUDED__AWRTS_CPlayerHuman

#include <Base/Vector3d.h>
#include <Base/Entities/IControllable.h>
#include <Graphics/Nodes/ICameraNode.h>

#include "IPlayer.h"

namespace awrts
{

// human-controlled human

class CPlayerHuman : public IPlayer, public hrengin::IControllable
{
public:
	CPlayerHuman(hrengin::graphics::ICameraNode* pPlayerCam);
	//void ApplyCamera();
	
	virtual bool ReceiveInput(hrengin::gui::InputEvent input)
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
	//hrengin::graphics::ICameraNode* mDefaultPOV;
	hrengin::graphics::ICameraNode* mPOV;
};

}

#endif//__H_INCLUDED__AWRTS_CPlayerHuman