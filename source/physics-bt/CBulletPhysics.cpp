/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <algorithm>

#include <hrengin/core/hrenginmodels.h>
#include <hrengin/core/IModel.h>
#include <hrengin/core/IModelLoader.h>

#include <hrengin/graphics/IVideoManager.h>

#include "CBulletPhysics.h"
#include "CPhysicsPhantom.h"
#include "CPhysicsBody.h"


namespace hrengin {
namespace physics {

class DebugDraw : public btIDebugDraw {
public:
	DebugDraw(graphics::IRenderingDevice* renderer)
	 : mode(DBG_NoDebug), vmgr_(renderer)
	{

	}

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		//workaround to bullet's inconsistent debug colors which are either from 0.0 - 1.0 or from 0.0 - 255.0

		Vector3d<f32> newColor;

		if (color[0] <= 1.0 && color[0] > 0.0) {
			newColor.X = ((u32)(color[0]*255.0));
		}
		if (color[1] <= 1.0 && color[1] > 0.0) {
			newColor.Y = ((u32)(color[1]*255.0));
		}
		if (color[2] <= 1.0 && color[2] > 0.0) {
			newColor.Z = ((u32)(color[2]*255.0));
		}

		vmgr_->drawLine(
		Vector3d<f32>(from[0], from[1], from[2]),
		Vector3d<f32>(to[0], to[1], to[2]),
		newColor);
	}
	

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		//   this->drawLine(PointOnB, PointOnB + normalOnB*distance, CONTACTPOINT_COLOR);

		const btVector3 to(PointOnB + normalOnB*distance);

		vmgr_->drawLine(
			Vector3d<f32>(PointOnB[0], PointOnB[1], PointOnB[2]),
			Vector3d<f32>(to[0], to[1], to[2]),
			Vector3d<f32>(255.0,255.0,255.0));
	}

	void reportErrorWarning(const char* text)
	{
		//this->logger->log(text, irr::ELL_ERROR);
	}

	void draw3dText(const btVector3& location, const char* text) { }

	void setDebugMode(int mode) { this->mode = mode; }

	int getDebugMode() const { return this->mode; }

private:
	DebugDraw(const DebugDraw& other) = delete;

	int mode;
	graphics::IRenderingDevice * vmgr_;
};


HRENGINPHYSICS_API IPhysicsManager* createPhysicsManager()
{
	return new CBulletPhysics();
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
	
	modelLoader_ = createModelLoader();


	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(0,0,0));
	
	btCollisionObject *collObject = new btCollisionObject();

	collObject->setCollisionShape(new btStaticPlaneShape(btVector3(0,1,0),0.0));
	collObject->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	
	m_dynamicsWorld->addCollisionObject(collObject,COL_GROUND,COL_GROUND | COL_DEBRIS); // 0000 0111

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

IDebugDrawer* CBulletPhysics::createDebugDrawer(graphics::IRenderingDevice* renderer)
{
	//debugDrawer_ = new CDebugDrawer();

	// temporary
	DebugDraw* debugDraw = new DebugDraw(renderer);
	debugDraw->setDebugMode(
		btIDebugDraw::DBG_DrawWireframe |
		btIDebugDraw::DBG_DrawAabb |
		btIDebugDraw::DBG_DrawContactPoints |
		//btIDebugDraw::DBG_DrawText |
		//btIDebugDraw::DBG_DrawConstraintLimits |
		btIDebugDraw::DBG_DrawConstraints //|
	);
	m_dynamicsWorld->setDebugDrawer(debugDraw);

	return 0;
}

void CBulletPhysics::debugDraw()
{
	m_dynamicsWorld->debugDrawWorld();
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

		//btVector3 aabbMin(1,1,1);
		//btVector3 aabbMax(2,2,2);
		
		btVector3 aabbMin(1,1,1);
		btVector3 aabbMax(2,2,2);
	}

	return true;
}

IPhysicsBody* CBulletPhysics::createBody(const char* modelName, Vector3d<f32> pos, u16 group, u16 filters)
{
	u32 shapeId = loadModel(modelName);
	return createBody(shapeId,pos, group,  filters); 
};

IPhysicsBody* CBulletPhysics::createBody(const u32 shapeid, Vector3d<f32> pos, u16 group, u16 filters)
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(pos.X,pos.Y,pos.Z));

	btScalar mass(1.0f);
	bool isDynamic = (mass != 0.f);
	btVector3 localInertia(0,0,0);
	btCollisionShape* colShape = collisionShapes_[shapeid];
	
	if (isDynamic) {
		colShape->calculateLocalInertia(mass,localInertia);
	}

	btDefaultMotionState* defaultMotionState = new btDefaultMotionState(defaultTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,defaultMotionState,colShape,localInertia);
	btRigidBody *rigidBody = new btRigidBody(rbInfo);

	if(group && filters) {
		m_dynamicsWorld->addRigidBody(rigidBody,group,filters);
	} else {
		m_dynamicsWorld->addRigidBody(rigidBody);
	}
	m_dynamicsWorld->updateAabbs();

	return new CPhysicsBody(rigidBody);
};

IPhysicsPhantom* CBulletPhysics::createPhantom(const char* modelName, u16 group, u16 filters)
{
	u32 shapeId = loadModel(modelName);
	return createPhantom(shapeId, filters); 
};

IPhysicsPhantom* CBulletPhysics::createPhantom(const u32 shapeid, u16 group, u16 filters)
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(0,0,0));
	
	btCollisionObject *collObject = new btCollisionObject();

	collObject->setCollisionShape(collisionShapes_[shapeid]);
	//collObject->setCollisionFlags (btCollisionObject::CF_NO_CONTACT_RESPONSE);
	collObject->setCollisionFlags (btCollisionObject::CF_KINEMATIC_OBJECT);
	
	m_dynamicsWorld->addCollisionObject(collObject,group,filters);
	//m_dynamicsWorld->updateAabbs();

	return new CPhysicsPhantom(collObject);
};

IPhysicsObject* CBulletPhysics::castRay(Vector3d<f32> from, Vector3d<f32> to, u16 filters)
{
	btVector3 btfrom = btVector3(from.X,from.Y,from.Z);
	btVector3 btto = btVector3(to.X,to.Y,to.Z);
	btCollisionWorld::ClosestRayResultCallback resultCallback(btfrom, btto);
	if(filters) {
		resultCallback.m_collisionFilterGroup = COL_UNIT;
		resultCallback.m_collisionFilterMask = filters;
	}

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
			btScalar(y),
			btScalar(z/2.0)));
	}

	if(shape.shape == SHAPE_CYLINDER) {
		if(z == 0.0) {
			z = x;
		}

		x /= 2.0;
		//y /= 2.0;
		z /= 2.0;

		switch(shape.axis) {
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
		switch(shape.axis) {
		case AXIS_X:
			return new btCapsuleShapeX(x,y);
		case AXIS_Y:
			return new btCapsuleShape(x,y);
		case AXIS_Z:
			return new btCapsuleShapeZ(x,y);
		}
	}
	
	if(shape.shape == SHAPE_CONE) {
		switch(shape.axis) {
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
			localTransform.setRotation(btQuaternion(primitive.rotation[1],primitive.rotation[0],primitive.rotation[2]));

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

	if(!model) {
		return 0;
	}
	
	u32 id = addShape(model);
	models_[modelName] = id;
	return id;
}



} // namespace physics
} // namespace hrengin
