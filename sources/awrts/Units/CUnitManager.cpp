
#include <Physics/IPhysicsPhantom.h>

#include "CUnit.h"
#include "UnitType.h"
#include "CUnitManager.h"
#include "../CApplication.h"

namespace awrts
{

CUnit& CUnitManager::createUnit(hrengin::u32 id, hrengin::Vector3d position, hrengin::f32 facing)
{
	UnitType unitType = unitTypes_[id];

	CUnit* unit = new CUnit(unitType, position, facing);
	
	units_.push_back(unit);

	CApplication& app = CApplication::getInstance();

	unit->visual_ = app.videomgr->CreateVisObject();
	unit->visual_->AddMesh(unitType.visualModelName);

	unit->selectionShape_ = app.phymgr->createPhantom(unitType.guiSelectionShapeId);
	unit->selectionShape_->attachToEntity(unit);
	unit->selectionShape_->setPosition(position);

	app.entmgr->addEntity(unit);

	return *unit;
};

void CUnitManager::addType(UnitType type)
{
	if(unitTypes_.find(type.id) == unitTypes_.end())
	{
		unitTypes_[type.id] = type;
	}
}

}