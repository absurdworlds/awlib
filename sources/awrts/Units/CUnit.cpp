
#include <Graphics/Nodes/IVisNode.h>
#include <Physics/IPhysicsPhantom.h>

#include "CUnit.h"
#include "CUnitType.h"


namespace awrts
{
	CUnitType& GetUnitType();
	hrengin::u32 GetUnitTypeID();

	CUnit::CUnit(CUnitType& pType)
		: mType(pType)
	{
		
	}

}