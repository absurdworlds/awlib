#ifndef __H_INCLUDED__HRENGIN_CEntityManager
#define __H_INCLUDED__HRENGIN_CEntityManager

#include <vector>
#include <deque>

#include <hrengin/entities/IBaseEntity.h>
#include <hrengin/entities/IEntityManager.h>

namespace hrengin
{

class CEntityManager : public IEntityManager
{
	private:
		class CNullEnt : public IBaseEntity
		{
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

#endif//__H_INCLUDED__HRENGIN_CEntityManager