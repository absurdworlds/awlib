#ifndef __H_INCLUDED__AWRTS_CUnitManager
#define __H_INCLUDED__AWRTS_CUnitManager

#include <vector>

//#include "CUnit.h"

namespace awrts
{

class CUnit;
class CUnitType;

class 
{
public:
	CUnit& CUnitManager(CUnitType& pType);
private:
	std::vector<CUnit> mUnits;

};

}

#endif//__H_INCLUDED__AWRTS_CUnitManager