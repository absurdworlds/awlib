
#include <Graphics/Nodes/IVisNode.h>
#include <Physics/IPhysicsPhantom.h>
#include <Base/Math/hrMath.h>


#include "CUnit.h"


namespace awrts
{
void CUnit::setPosition(hrengin::Vector3d position)
{
	position_ = position;
}

void CUnit::setRotation(hrengin::Vector3d rotation)
{
	rotation_ = rotation;
}

void CUnit::sync()
{
	visual_->setPosition(position_);
	selectionShape_->setPosition(position_);
	visual_->setRotation(rotation_);
	selectionShape_->setRotation(position_);
}

void CUnit::think(hrengin::u32 time)
{
	//reminder: rewrite it to setNextThink 

	switch(order_.orderId)
	{
	case ORDER_MOVE:
	{
		hrengin::Vector3d direction(order_.targetX,0,order_.targetY);
		direction -= position_;

		if(direction.squareLength() < 0.5)
		{
			order_.orderId = ORDER_STOP;
		}
		else
		{
			setRotation(hrengin::Vector3d(0,180,0) + direction.getHorizontalAngle());
			setPosition(position_ + 0.5 * direction.normalized());
		}

		break;
	}
	default:
		break;
	}
}

/*UnitType& CUnit::getUnitType()
{
	return type_;
}*/

hrengin::u32 CUnit::getUnitTypeID()
{
	return typeId;
}

CUnit::CUnit(UnitType& type, hrengin::Vector3d position, hrengin::f32 facing)
	: typeId(type.id), position_(position), rotation_(hrengin::Vector3d(0,facing,0))
{

}

bool CUnit::issuePointOrder(OrderId order, hrengin::Vector3d pos)
{
	switch(order)
	{
	case ORDER_MOVE:
		break;
	default:
		return false;
	}

	order_.orderId = order;
	order_.targetX = pos.X;
	order_.targetY = pos.Z;
	return true;
}

void getStringFromUnitId(hrengin::u32 unitId, unsigned char* output)
{
	output[0] = (unitId >> 24) & 0xFF;
	output[1] = (unitId >> 16) & 0xFF;
	output[2] = (unitId >> 8)  & 0xFF;
	output[3] = (unitId >> 0)  & 0xFF;
	output[4] = 0;
}

} // end namespace awrts