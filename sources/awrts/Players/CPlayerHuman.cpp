#include "CPlayerHuman.h"

#define VER_storm_in_a_bottle 01000
#define VER_srantonwars 02000

#define AWRTS_VER 00000

namespace awrts
{

CPlayerHuman::CPlayerHuman(hrengin::graphics::ICameraNode* pPlayerCam)
	: PlayerInputDisabled(false), mPOV(pPlayerCam)
{
	pPlayerCam->SetBehavior(hrengin::graphics::ICameraNode::CAM_STRATEGIC);
	//mCurrentPOV = mDefaultPOV = pPlayerCam;
	
}


}