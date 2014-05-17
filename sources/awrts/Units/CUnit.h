#ifndef __H_INCLUDED__AWRTS_CUnit
#define __H_INCLUDED__AWRTS_CUnit

#include <Common/hrTypes.h>
#include <Base/Entities/IBaseEntity.h>

//#include "CUnitManager.h"

namespace hrengin
{
	namespace physics
	{
		class IPhysicsPhantom;
	}

	namespace graphics
	{
		class IVisNode;
	}
}


namespace awrts
{
	class CUnitType;
	class CUnitManager;

class CUnit : public hrengin::IBaseEntity
{
	friend class CUnitManager;
	//friend CUnit& CUnitManager::createUnit(hrengin::u32 id);
public:
	CUnit(CUnitType& pType);
	CUnitType& getUnitType();
	hrengin::u32 getUnitTypeID();

	virtual void OnParentRemove() {};

	virtual bool Sync() {return 0;};

	virtual bool SetPosition() {return 0;};
	virtual bool SetRotation() {return 0;};
	virtual void EnterDeleteQueue() {};

private:
	CUnitType& mType;
	hrengin::graphics::IVisNode*		mVisual;
	hrengin::physics::IPhysicsPhantom*	mSelectionShape;
};

}

#endif//__H_INCLUDED__AWRTS_CUnit