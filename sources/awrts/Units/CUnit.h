#ifndef __H_INCLUDED__AWRTS_CUnit
#define __H_INCLUDED__AWRTS_CUnit

#include <Base/hrTypes.h>

#include "CUnitManager.h"

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

class CUnit
{
	friend CUnit& CUnitManager::createUnit(CUnitType& pType);
public:
	CUnitType& getUnitType();
	hrengin::u32 getUnitTypeID();

private:
	CUnit(CUnitType& pType);

	CUnitType& mType;
	hrengin::graphics::IVisNode*		mVisual;
	hrengin::physics::IPhysicsPhantom*	mSelectionShape;
};

}

#endif//__H_INCLUDED__AWRTS_CUnit