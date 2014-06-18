#ifndef __H_INCLUDED__AWRTS_CUnit
#define __H_INCLUDED__AWRTS_CUnit

#include <hrengin/common/hrTypes.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/entities/IBaseEntity.h>
#include <hrengin/entities/IThinking.h>
#include "UnitType.h"

//#include "CUnitManager.h"

namespace hrengin {
namespace physics {
	class IPhysicsPhantom;
}

namespace graphics {
	class IVisNode;
}
}

namespace awrts
{
	class CUnitManager;

enum OrderId
{
	ORDER_NONE = 0,
	ORDER_MOVE = 'omov',
	ORDER_STAND = 'osta',
	ORDER_STOP = 'osto'
};

class CUnit : public hrengin::IThinking
{
		friend class CUnitManager;
		//friend CUnit& CUnitManager::createUnit(hrengin::u32 id);
	private:
		hrengin::u32 typeId;
		hrengin::graphics::IVisNode*		visual_;
		hrengin::physics::IPhysicsPhantom*	selectionShape_;
		hrengin::Vector3d position_;
		hrengin::Vector3d rotation_;

		struct 
		{
			OrderId orderId;
			union
			{
				hrengin::u32 targetId;
				struct 
				{
					hrengin::f32 targetX;
					hrengin::f32 targetY;
				};
			};
		} order_;

		hrengin::u32 eventId_;
	public:
		//UnitType& getUnitType();
		hrengin::u32 getUnitTypeID();
		virtual hrengin::u32 getEntityIdentifier()
		{
			return 'unit';
		}

		virtual void onParentRemove() {};

		virtual void sync();
		virtual void think(hrengin::u32 time);

		virtual void setPosition(hrengin::Vector3d position);
		virtual void setRotation(hrengin::Vector3d rotation);
		virtual void enterDeleteQueue() {};

		virtual bool issuePointOrder(OrderId order, hrengin::Vector3d pos);

	private:
		CUnit(UnitType& type, hrengin::Vector3d position, hrengin::f32 facing);
};

void getStringFromUnitId(hrengin::u32 unitId, unsigned char* output);

}


#endif//__H_INCLUDED__AWRTS_CUnit