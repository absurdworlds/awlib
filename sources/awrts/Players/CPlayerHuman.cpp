#include <Base/Vector3d.h>
#include <Irrlicht/plane3d.h>
#include <Irrlicht/Vector3d.h>

#include <Physics/Base/IPhysicsObject.h>

#include "../CApplication.h"
#include "../Units/CUnit.h"
#include "../Units/CUnitManager.h"

#include "CPlayerHuman.h"

#define VER_storm_in_a_bottle 01000
#define VER_srantonwars 02000

#define AWRTS_VER 00000

namespace awrts
{

CPlayerHuman::CPlayerHuman(hrengin::graphics::ICameraNode* pPlayerCam)
	: PlayerInputDisabled(false), povCamera_(pPlayerCam),
	tmpSelUnit_(0)
{
	pPlayerCam->SetBehavior(hrengin::graphics::ICameraNode::CAM_STRATEGIC);
	//mCurrentPOV = mDefaultPOV = pPlayerCam;
	
}


CUnit* CPlayerHuman::getUnitFromRay(hrengin::base::line3df ray)
{
	CApplication& app = CApplication::getInstance();
	
	hrengin::Vectorf3d start(ray.end.X,
				             ray.end.Y,
				             ray.end.Z);
	hrengin::Vectorf3d end(ray.start.X,
						   ray.start.Y,
				           ray.start.Z);

	hrengin::physics::IPhysicsObject* rayHit = app.phymgr->castRay(start,end);

	if(!rayHit)
	{
		return 0;
	}

	hrengin::IBaseEntity* foundEntity = rayHit->getEntity();

	if(foundEntity->getEntityIdentifier() != 'unit')
	{
		return 0;
	}

	return static_cast<CUnit*>(foundEntity);
}

	/*printf("--mous--\n");
	printf("%d\n",x);
	printf("%d\n",y);
	printf("--line--\n");
	printf("%.5f\n",start.X);
	printf("%.5f\n",start.Y);
	printf("%.5f\n",start.Z);
	printf("--end--\n");
	printf("%.5f\n",end.X);
	printf("%.5f\n",end.Y);
	printf("%.5f\n",end.Z);*/

	/*if(__HRIM.physmgr->castRay(start, end))
	{
		printf("!\n");
		
		printf("%d\n",__HRIM.physmgr);
		printf("%d\n",__HRIM.physmgr->castRay(start, end));
		return __HRIM.physmgr->castRay(start, end)->getEntity();
	};
	
	return 0;*/

bool CPlayerHuman::ReceiveInput(hrengin::gui::InputEvent input)
{
	static hrengin::i32 X = 400, Y = 300;
	static CApplication& app = CApplication::getInstance();

	if(input.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		X = input.MouseInput.X;
		Y = input.MouseInput.Y;
		if(input.MouseInput.Event==irr::EMIE_LMOUSE_PRESSED_DOWN)
		{
			hrengin::base::line3df ray = povCamera_->castRayFromScreen(input.MouseInput.X,  input.MouseInput.Y);
			CUnit* rayHit = getUnitFromRay(ray);
			if(rayHit)
			{
				unsigned char unitId[5];
				getStringFromUnitId(rayHit->getUnitTypeID(),unitId);
				fprintf(stderr, "%s: Standing by\n", unitId);
				tmpSelUnit_ = rayHit;
			}
			else if(tmpSelUnit_)
			{
				unsigned char unitId[5];
				getStringFromUnitId(tmpSelUnit_->getUnitTypeID(),unitId);
				fprintf(stderr, "%s: Affirmative!\n", unitId);
				hrengin::Vector3d pos = povCamera_->__tempGetRayHitPlaneCoords(X,Y);
				tmpSelUnit_->issuePointOrder(ORDER_MOVE, pos);
			}
		}
	}
else if (input.EventType == irr::EET_KEY_INPUT_EVENT)
{
	static int numbers = 0;
	printf("knopkodoska input %d; %d\n", ++numbers, app.encore->GetTime());
	if(input.KeyInput.Key == irr::KEY_KEY_I && input.KeyInput.PressedDown)
	{
		hrengin::base::line3df ray = povCamera_->castRayFromScreen(X,Y);
		CUnit* rayHit = getUnitFromRay(ray);
		if(!rayHit)
		{
			CUnitManager* umgr =  app.unitmgr;
			static unsigned int lastId = 0;
			unsigned int unitId;
			int i = 0;
			for(std::unordered_map<hrengin::u32,UnitType>::iterator it = umgr->unitTypes_.begin();
				it != umgr->unitTypes_.end();
				++it,++i)
			{
				if(lastId % umgr->unitTypes_.size() == i) unitId = (*it).second.id;
			}
			
			
			hrengin::Vector3d pos = povCamera_->__tempGetRayHitPlaneCoords(X,Y);
			app.unitmgr->createUnit(unitId,pos);

			++ lastId;
		}
	}
	}


	return false;
}

}