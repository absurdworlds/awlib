
#include <Graphics/Nodes/IVisNode.h>
#include <Physics/IPhysicsPhantom.h>

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
	
void getStringFromUnitId(hrengin::u32 unitId, unsigned char* output)
{
	output[0] = (unitId >> 24) & 0xFF;
	output[1] = (unitId >> 16) & 0xFF;
	output[2] = (unitId >> 8)  & 0xFF;
	output[3] = (unitId >> 0)  & 0xFF;
	output[4] = 0;
}

}