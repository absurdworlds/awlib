
#include <algorithm>

#include <hrengin/core/hrenginmodels.h>
#include <hrengin/core/IModel.h>
#include <hrengin/core/IModelLoader.h>

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
	
	modelLoader_ = createModelLoader();

	btCollisionShape* Shape = new btEmptyShape;
	collisionShapes_.push_back(Shape);
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
	for (int j=0; j<collisionShapes_.size(); j++)
	{
		btCollisionShape* shape = collisionShapes_[j];
		delete shape;
	}
	collisionShapes_.clear();

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

IPhysicsPhantom* CBulletPhysics::createPhantom(const char* modelName) 
{
	u32 shapeId = loadModel(modelName);
	return createPhantom(shapeId); 
};

IPhysicsPhantom* CBulletPhysics::createPhantom(const u32 shapeid) 
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(0,0,0));
	
	btCollisionObject *collObject = new btCollisionObject();

	collObject->setCollisionShape(collisionShapes_[shapeid]);
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

btCollisionShape* CBulletPhysics::createPrimitiveShape(SPrimitive shape) 
{
	btScalar x = shape.dimensions[0], 
		y = shape.dimensions[1], 
		z = shape.dimensions[2];

	if(shape.shape == SHAPE_SPHERE) {
		return new btSphereShape(x);
	}

	if(shape.shape == SHAPE_BOX) {
		return new btBoxShape(btVector3(
			btScalar(x/2.0),
			btScalar(y/2.0),
			btScalar(z/2.0)));
	}

	if(shape.shape == SHAPE_CYLINDER) {
		switch(shape.axis)
		{
		case AXIS_X:
			return new btCylinderShapeX(btVector3(
				btScalar(x),btScalar(y),btScalar(z)));
		case AXIS_Y:
			return new btCylinderShape(btVector3(
				btScalar(x),btScalar(y),btScalar(z)));
		case AXIS_Z:
			return new btCylinderShapeZ(btVector3(
				btScalar(x),btScalar(y),btScalar(z)));
		}
	}
	
	if(shape.shape == SHAPE_CAPSULE) {
		switch(shape.axis)
		{
		case AXIS_X:
			return new btCapsuleShapeX(x,y);
		case AXIS_Y:
			return new btCapsuleShape(x,y);
		case AXIS_Z:
			return new btCapsuleShapeZ(x,y);
		}
	}
	
	if(shape.shape == SHAPE_CONE)
	{
		switch(shape.axis)
		{
		case AXIS_X:
			return new btConeShapeX(x,y);
		case AXIS_Y:
			return new btConeShape(x,y);
		case AXIS_Z:
			return new btConeShapeZ(x,y);
		}
	}

	return new btEmptyShape;
}

u32 CBulletPhysics::addShape(IModel* model)
{
	if(model->primitives.size() > 0) {
		btCompoundShape* compound = new btCompoundShape();
	
		for(auto it = model->primitives.begin(); it != model->primitives.end(); it++) {
			SPrimitive primitive = *it;
			btCollisionShape * shape = createPrimitiveShape(primitive);
			btTransform localTransform;

			localTransform.setIdentity();
			localTransform.setOrigin(btVector3(primitive.offset[0],primitive.offset[1],primitive.offset[2]));
			localTransform.setRotation(btQuaternion(primitive.rotation[0],primitive.rotation[1],primitive.rotation[2]));

			compound->addChildShape(localTransform,shape);
		}

		collisionShapes_.push_back(compound);
	} else {
		return 0;
	}	

	return collisionShapes_.size()-1;
};


u32 CBulletPhysics::loadModel(const char* modelName)
{
	auto modelId = models_.find(modelName);
	if(modelId != models_.end()) {
		return modelId->second;
	}

	IModel* model = modelLoader_->loadModel(modelName);

	return addShape(model);
}



} // namespace physics
} // namespace hrengin
