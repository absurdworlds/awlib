#ifndef _hrengin_CEntityManager_
#define _hrengin_CEntityManager_

#include <vector>
#include <deque>

#include <hrengin/game/IBaseEntity.h>
#include <hrengin/game/IEntityManager.h>

namespace hrengin {

class CEntityManager : public IEntityManager {
private:
	class CNullEnt : public IBaseEntity {
		public:
			void sync() {};
			void setPosition(Vector3d position) {};
			void setRotation(Vector3d position) {};
			void onParentRemove() {};
			void enterDeleteQueue() {};
	} nullEntity;

	std::deque<IBaseEntity*> entlist_;
	std::vector<u32> freelist_;
public:
	CEntityManager();

	virtual void doSync();
		
	virtual void addEntity(IBaseEntity* entity);
	virtual void deleteEntity(u32 entid);
};

	
} // namespace hrengin

#endif//_hrengin_CEntityManager_