
#ifndef __HG_CBulletPhysics__
#define __HG_CBulletPhysics__

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <Physics/Base/IPhysicsManager.h>

#include "CPhysicsPhantom.h"

namespace hrengin
{
namespace physics
{

class CBulletPhysics : public IPhysicsManager
{
	public:
		CBulletPhysics();
		~CBulletPhysics();

		btScalar getDeltaTime()
		{
			btScalar dt = (btScalar)m_clock.getTimeMicroseconds();
			m_clock.reset();
			return dt;
		}

		virtual IPhysicsBody* CreateBody(const u32 shapeid) {return 0;};
		virtual IPhysicsPhantom* CreatePhantom(const u32 shapeid);

		virtual u32 AddShape(const char * modelname) {return 0;};
		virtual u32 MakeShape(IPhysicsManager::PHYS_BUILTIN_SHAPES type, f32 x, f32 y=1., f32 z=1.);

		virtual IPhysicsObject* CastRay(Vectorf3d from, Vectorf3d to);

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

#endif//__HG_CBulletPhysics__