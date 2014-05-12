
#ifndef __HG_hrcBulletPhysics__
#define __HG_hrcBulletPhysics__

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <Physics/Base/hriPhysicsManager.h>

#include "hrcPhysicsPhantom.h"

namespace hrengin
{
namespace physics
{

class hrcBulletPhysics : public hriPhysicsManager
{
	public:
		hrcBulletPhysics();
		~hrcBulletPhysics();

		btScalar getDeltaTime()
		{
			btScalar dt = (btScalar)m_clock.getTimeMicroseconds();
			m_clock.reset();
			return dt;
		}

		virtual hriPhysicsBody* CreateBody(const u32 shapeid) {return 0;};
		virtual hriPhysicsPhantom* CreatePhantom(const u32 shapeid);

		virtual u32 AddShape(const char * modelname) {return 0;};
		virtual u32 MakeShape(hriPhysicsManager::PHYS_BUILTIN_SHAPES type, f32 x, f32 y=1., f32 z=1.);

		virtual hriPhysicsObject* CastRay(Vectorf3d from, Vectorf3d to);

		virtual bool Step();

	private:		
		btClock	m_clock;

		btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

		btDefaultCollisionConfiguration*		m_collisionConfiguration;

		btBroadphaseInterface*	m_broadphase;
		btCollisionDispatcher*	m_dispatcher;
		btConstraintSolver*		m_solver;

		btDynamicsWorld*		m_dynamicsWorld;
};

} // namespace physics
} // namespace hrengin

#endif//__HG_hrcBulletPhysics__