#include <Base/Vector3d.h>
#include "../CApplication.h"

#include "../Units/CUnit.h"
#include "CPlayerHuman.h"

#define VER_storm_in_a_bottle 01000
#define VER_srantonwars 02000

#define AWRTS_VER 00000

namespace awrts
{

CPlayerHuman::CPlayerHuman(hrengin::graphics::ICameraNode* pPlayerCam)
	: PlayerInputDisabled(false), povCamera_(pPlayerCam)
{
	pPlayerCam->SetBehavior(hrengin::graphics::ICameraNode::CAM_STRATEGIC);
	//mCurrentPOV = mDefaultPOV = pPlayerCam;
	
}

	
bool CPlayerHuman::ReceiveInput(hrengin::gui::InputEvent input)
{
	if(input.type == input.INPUT_MOUSE_EVENT)
	{
		if(input.MouseInput.type==0)
			{
			hrengin::IBaseEntity* bus = povCamera_->castRayFromScreen(input.MouseInput.X,  input.MouseInput.Y);
			if(bus)
			{
				unsigned char bytes[4];
				//unsigned long n = static_cast<CUnit*>(bus)->getUnitTypeID();
				unsigned long n = (bus)->getEntityIdentifier();

				bytes[0] = (n >> 24) & 0xFF;
				bytes[1] = (n >> 16) & 0xFF;
				bytes[2] = (n >> 8) & 0xFF;
				bytes[3] = n & 0xFF;
				fprintf(stderr, "Ray hit: %c%c%c%c\n", bytes[0],bytes[1],bytes[2],bytes[3]);
			}
			
		}
	}

	return false;
}

}