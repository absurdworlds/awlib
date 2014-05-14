#include "CPlayerHuman.h"

namespace awrts
{

CPlayerHuman::CPlayerHuman(hrengin::graphics::hriCameraNode* pPlayerCam)
	: PlayerInputDisabled(false), mPOV(pPlayerCam)
{
	pPlayerCam->SetBehavior(hrengin::graphics::hriCameraNode::CAM_STRATEGIC);
	//mCurrentPOV = mDefaultPOV = pPlayerCam;
	
}


}