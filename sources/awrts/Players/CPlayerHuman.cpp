
#include <Irrlicht/plane3d.h>
#include <Irrlicht/Vector3d.h>

#include <hrengin/common/Vector3d.h>
#include <hrengin/base/ILogger.h>

#include <hrengin/physics/IPhysicsObject.h>

#include <hrengin/sound/ISoundManager.h>

#include "../CApplication.h"
#include "../Units/CUnit.h"
#include "../Units/CUnitManager.h"

#include "CPlayerHuman.h"

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
	// todo: intentionally swap end and start to make funny bugs
	hrengin::Vectorf3d start(ray.start.X, ray.start.Y, ray.start.Z);
	hrengin::Vectorf3d end(ray.end.X, ray.end.Y, ray.end.Z);

	hrengin::physics::IPhysicsObject* rayHit = app.phymgr.castRay(start,end);

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
				hrengin::sound::getSoundManager().playSound("generic2_ready01.wav");
				tmpSelUnit_ = rayHit;
			}
			else if(tmpSelUnit_)
			{
				unsigned char unitId[5];
				getStringFromUnitId(tmpSelUnit_->getUnitTypeID(),unitId);
				fprintf(stderr, "%s: Affirmative!\n", unitId);
				hrengin::sound::getSoundManager().playSound("generic2_yes01.wav");
				hrengin::Vector3d pos = povCamera_->__tempGetRayHitPlaneCoords(X,Y);
				tmpSelUnit_->issuePointOrder(ORDER_MOVE, pos);
			}
		}
	}
	else if (input.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		static int numbers = 0;
		//hrengin::CLogger::log("knopkodoska input " + std::to_string(app.encore->GetTime()) + "\n");
		if(input.KeyInput.Key == irr::KEY_KEY_I && input.KeyInput.PressedDown)
		{
			hrengin::base::line3df ray = povCamera_->castRayFromScreen(X,Y);
			CUnit* rayHit = getUnitFromRay(ray);
			if(!rayHit)
			{
				CUnitManager& umgr = app.unitmgr;
				static unsigned int lastId = 0;
				unsigned int unitId;
				int i = 0;
				for(std::unordered_map<hrengin::u32,UnitType>::iterator it = umgr.unitTypes_.begin();
					it != umgr.unitTypes_.end();
					++it,++i) {
					if(lastId % umgr.unitTypes_.size() == i) {
						unitId = (*it).second.id;
					}
				}

				hrengin::Vector3d pos = povCamera_->__tempGetRayHitPlaneCoords(X,Y);
				app.unitmgr.createUnit(unitId,pos);

				++ lastId;
			}
		}
		else if (input.KeyInput.Key == irr::KEY_KEY_U && input.KeyInput.PressedDown)
		{
			hrengin::getLogger().push("DEBUG:");
			hrengin::getLogger().push(std::to_string(app.unitmgr.getUnitCount()));
			hrengin::getLogger().push(hrengin::endl);
		} else if (input.KeyInput.Key == irr::KEY_KEY_P && input.KeyInput.PressedDown)
		{
			app.profiling = !app.profiling;
			hrengin::getLogger().push("DEBUG: Profiling =");
			hrengin::getLogger().push(std::to_string(app.profiling));
			hrengin::getLogger().push(hrengin::endl);
		}
	}


	return false;
}

}