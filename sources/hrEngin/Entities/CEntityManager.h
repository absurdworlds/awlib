#ifndef __H_INCLUDED__HRENGIN_CEntityManager
#define __H_INCLUDED__HRENGIN_CEntityManager

#include <vector>
#include <deque>

#include <Entities/IBaseEntity.h>
#include <Base/IEntityManager.h>

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

		std::vector<IBaseEntity*> entlist_;
		std::deque<u32> deleteQueue_;
		std::vector<u32> freelist_;
	public:
		CEntityManager();

		virtual void doSync();
		virtual void doCleanup();
		
		virtual void addEntity(IBaseEntity* entity);
		virtual void deleteEntity(u32 entid);
};

	
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_CEntityManager