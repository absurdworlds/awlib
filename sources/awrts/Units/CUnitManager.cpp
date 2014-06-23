
#include <hrengin/common/hrengintime.h>
#include <hrengin/physics/IPhysicsPhantom.h>
#include <hrengin/entities/IEventManager.h>
#include <hrengin/graphics/IVisNode.h>

#include "CUnit.h"
#include "UnitType.h"
#include "CUnitManager.h"
#include "../CApplication.h"

namespace awrts {

CUnit& CUnitManager::createUnit(hrengin::u32 id, hrengin::Vector3d position, hrengin::f32 facing)
{
	UnitType unitType = unitTypes_[id];

	CUnit* unit = new CUnit(unitType, position, facing);
	
	units_.push_back(unit);

	CApplication& app = CApplication::getInstance();

	unit->visual_ = app.videomgr.CreateVisObject();
	unit->visual_->AddMesh(unitType.visualModelName);

	unit->selectionShape_ = app.phymgr.createPhantom(unitType.guiSelectionShapeId);
	unit->selectionShape_->attachToEntity(unit);
	unit->selectionShape_->setPosition(position);

	hrengin::Event thinkEvent;
	thinkEvent.owner = unit;
	thinkEvent.isActive = true;
	thinkEvent.nextFire = hrengin::getTime() + 30;
	thinkEvent.period = 20;

	unit->eventId_ = app.eventmgr.addEvent(thinkEvent);

	app.entmgr.addEntity(unit);

	unit->sync();

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