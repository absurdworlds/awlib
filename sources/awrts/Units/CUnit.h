#ifndef __H_INCLUDED__AWRTS_CUnit
#define __H_INCLUDED__AWRTS_CUnit

#include <Common/hrTypes.h>
#include <Base/Vector3d.h>
#include <Entities/IBaseEntity.h>
#include "UnitType.h"

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
	class CUnitManager;

class CUnit : public hrengin::IBaseEntity
{
		friend class CUnitManager;
		//friend CUnit& CUnitManager::createUnit(hrengin::u32 id);
	private:
		hrengin::u32 typeId;
		hrengin::graphics::IVisNode*		visual_;
		hrengin::physics::IPhysicsPhantom*	selectionShape_;
		hrengin::Vector3d position_;
		hrengin::Vector3d rotation_;
	public:
		//UnitType& getUnitType();
		hrengin::u32 getUnitTypeID();
		virtual hrengin::u32 getEntityIdentifier()
		{
			return 'unit';
		}

		virtual void onParentRemove() {};

		virtual void sync();

		virtual void setPosition(hrengin::Vector3d position);
		virtual void setRotation(hrengin::Vector3d rotation);
		virtual void enterDeleteQueue() {};

	private:
		CUnit(UnitType& type, hrengin::Vector3d position, hrengin::f32 facing);
};

}

#endif//__H_INCLUDED__AWRTS_CUnit