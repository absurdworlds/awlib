/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_EntityManager_impl_
#define _awrts_EntityManager_impl_

#include <vector>
#include <deque>

#include <awrts/math/Vector3d.h>

#include <awrts/game/Entity.h>
#include <awrts/game/EntityManager.h>

namespace awrts {
namespace game {
namespace impl_ {
class EntityManager : public game::EntityManager {
public:
	EntityManager();

	virtual void doSync();

	virtual void addEntity(Entity* entity);
	virtual void deleteEntity(u32 entid);
private:
	class NullEnt : public Entity {
	public:
		void sync() {};
		void setPosition(Vector3d<f32> position) {};
		void setRotation(Vector3d<f32> position) {};
		Vector3d<f32> getPosition() const
		{
			return Vector3d<f32>(0,0,0);
		}
		Vector3d<f32> getRotation() const
		{
			return Vector3d<f32>(0,0,0);
		}
		void onParentRemove() {};
		void enterDeleteQueue() {};
	} nullEntity;

	typedef std::deque<Entity*>::iterator ent_iterator;

	std::deque<Entity*> entlist_;
	std::vector<u32> freelist_;
};
} // namespace impl_
} // namespace game
} // namespace awrts
#endif//_awrts_EntityManager_impl_
