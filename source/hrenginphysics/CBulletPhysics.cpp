
#include <stdio.h>

#include <hrengin/core/hrenginmodels.h>

#include "CBulletPhysics.h"


namespace hrengin {
namespace physics {

HRENGINPHYSICS_API IPhysicsManager& getPhysicsManager()
{
	static CBulletPhysics singleton;
	return singleton;
}

CBulletPhysics::CBulletPhysics()
{	
	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();
	
	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);
	m_dynamicsWorld->setGravity(btVector3(0,-10,0));
	//m_dynamicsWorld->setDebugDrawer(&gDebugDraw);
	
}

CBulletPhysics::~CBulletPhysics()
{	
	//cleanup in the reverse order of creation/initialization

	//remove the rigidbodies from the dynamics world and delete them
	int i;
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0; j<m_collisionShapes.size(); j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}
	m_collisionShapes.clear();

	delete m_dynamicsWorld;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfiguration;
}

btScalar CBulletPhysics::getDeltaTime()
{
	btScalar dt = (btScalar)m_clock.getTimeMicroseconds();
	m_clock.reset();
	return dt;
}

u32 CBulletPhysics::makeShape(IPhysicsManager::PhysShape type, f32 x, f32 y, f32 z)
{
	//rewrite to switch
	if(type == PHYS_SHAPE_BOX)
	{
		btBoxShape* Shape = new btBoxShape(btVector3(btScalar(x),btScalar(y),btScalar(z)));
		m_collisionShapes.push_back(Shape);
	}
	else if(type == PHYS_SHAPE_CYLINDER)
	{
		btCylinderShape* Shape = new btCylinderShape(btVector3(btScalar(x),btScalar(y),btScalar(z)));
		m_collisionShapes.push_back(Shape);
	}
	else if(type == PHYS_SHAPE_SPHERE)
	{
		btSphereShape* Shape = new btSphereShape(x);
		m_collisionShapes.push_back(Shape);
	}
	else if(type == PHYS_SHAPE_CAPSULE)
	{
		btCapsuleShape* Shape = new btCapsuleShape(x,y);
		m_collisionShapes.push_back(Shape);
	}
	else if(type == PHYS_SHAPE_CONE)
	{
		btConeShape* Shape = new btConeShape(x,y);
		m_collisionShapes.push_back(Shape);
	}
	else
	{
		return 1<<31;
	}
	return m_collisionShapes.size()-1;
}

IPhysicsPhantom* CBulletPhysics::createPhantom(const u32 shapeid) 
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(0,0,0));
	
	btCollisionObject *collObject = new btCollisionObject();

	collObject->setCollisionShape(m_collisionShapes[shapeid]);
	collObject->setCollisionFlags (btCollisionObject::CF_NO_CONTACT_RESPONSE);
	
	m_dynamicsWorld->addCollisionObject(collObject);
	//m_dynamicsWorld->updateAabbs();

	return new CPhysicsPhantom(collObject);
};

IPhysicsObject* CBulletPhysics::castRay(Vectorf3d from, Vectorf3d to)
{
	btVector3 btfrom = btVector3(from.X,from.Y,from.Z);
	btVector3 btto = btVector3(to.X,to.Y,to.Z);
	btCollisionWorld::ClosestRayResultCallback resultCallback(btfrom, btto);
	m_dynamicsWorld->rayTest(btfrom, btto, resultCallback);

	if (resultCallback.hasHit())
	{
		return (IPhysicsObject*)resultCallback.m_collisionObject->getUserPointer();
	}

	return 0;
}

bool CBulletPhysics::step()
{
	//simple dynamics world doesn't handle fixed-time-stepping
	float ms = getDeltaTime();
	
	//step the simulation
	if (m_dynamicsWorld)
	{
		m_dynamicsWorld->stepSimulation(ms / 1000000.f);
		//optional but useful: debug drawing
		//m_dynamicsWorld->debugDrawWorld();

		//btVector3 aabbMin(1,1,1);
		//btVector3 aabbMax(2,2,2);

		//MyOverlapCallback aabbOverlap(aabbMin,aabbMax);
		//m_dynamicsWorld->getBroadphase()->aabbTest(aabbMin,aabbMax,aabbOverlap);
		
		/*if (aabbOverlap.m_numOverlap)
			printf("#aabb overlap = %d\n", aabbOverlap.m_numOverlap);*/
	}

	return true;
}


u32 CBulletPhysics::loadModel(const char* modelName)
{

}



} // namespace physics
} // namespace hrengin
