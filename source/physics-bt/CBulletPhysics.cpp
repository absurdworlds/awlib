/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <algorithm>

#include <hrengin/core/models.h>
#include <hrengin/core/IModel.h>
#include <hrengin/core/IModelLoader.h>

#include <hrengin/graphics/IVideoManager.h>

#include "CBulletPhysics.h"
#include "CPhysicsWorld.h"
#include "CCollisionPhantom.h"
#include "CRigidBody.h"
#include "hrToBullet.h"
#include "CDebugDrawer.h"


namespace hrengin {
namespace physics {


HRENGINPHYSICS_API IPhysicsManager* createPhysicsManager()
{
	return new CBulletPhysics();
}

CBulletPhysics::CBulletPhysics()
{
	modelLoader_ = createModelLoader();
	
	// Add a 'fallback' empty shape, used if loading of some shape is failed
	btCollisionShape* shape = new btEmptyShape;
	collisionShapes_.push_back(shape);
}

CBulletPhysics::~CBulletPhysics()
{
	for (int j=0; j<collisionShapes_.size(); j++) {
		btCollisionShape* shape = collisionShapes_[j];
		delete shape;
	}
	collisionShapes_.clear();
}

IPhysicsWorld* CBulletPhysics::createPhysicsWorld()
{
	//collision configuration contains default setup for memory, collision setup
	btCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	//m_collisionConfiguration->setConvexConvexMultipointIterations();
	
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	
	//the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	return new CPhysicsWorld(collisionConfiguration, broadphase,
		dispatcher, solver);
}

IDebugDrawer* CBulletPhysics::createDebugDrawer(graphics::IRenderingDevice* renderer)
{
	return new CDebugDrawer(renderer);
}

IRigidBody* CBulletPhysics::createBody(const char* modelName, IRigidBody::RigidBodyConstructionInfo cInfo)
{
	u32 shapeId = loadModel(modelName);
	return createBody(shapeId, cInfo); 
};

IRigidBody* CBulletPhysics::createBody(const u32 shapeid, IRigidBody::RigidBodyConstructionInfo cInfo)
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(toBullet(cInfo.position));

	btCollisionShape* colShape = collisionShapes_[shapeid];

	btScalar mass(cInfo.mass);

	bool isDynamic = (mass != 0.f);
	btVector3 localInertia(0,0,0);
	
	if (isDynamic) {
		colShape->calculateLocalInertia(mass,localInertia);
	}

	btDefaultMotionState* defaultMotionState = new btDefaultMotionState(defaultTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,
		defaultMotionState,colShape,localInertia);

	rbInfo.m_friction = cInfo.friction;
	rbInfo.m_rollingFriction = cInfo.rollingFriction;
	rbInfo.m_restitution = cInfo.restitution;
	rbInfo.m_angularDamping = cInfo.angularDamping;
	rbInfo.m_linearDamping = cInfo.linearDamping;

	btRigidBody *rigidBody = new btRigidBody(rbInfo);

	return new CRigidBody(rigidBody);
};

ICollisionPhantom* CBulletPhysics::createPhantom(const char* modelName)
{
	u32 shapeId = loadModel(modelName);
	return createPhantom(shapeId); 
};

ICollisionPhantom* CBulletPhysics::createPhantom(const u32 shapeid)
{
	btTransform defaultTransform;
	defaultTransform.setIdentity();
	defaultTransform.setOrigin(btVector3(0,0,0));
	
	btCollisionObject *collObject = new btCollisionObject();

	collObject->setCollisionShape(collisionShapes_[shapeid]);
	//collObject->setCollisionFlags (btCollisionObject::CF_NO_CONTACT_RESPONSE);
	collObject->setCollisionFlags (btCollisionObject::CF_KINEMATIC_OBJECT);

	return new CCollisionPhantom(collObject);
};

btCollisionShape* CBulletPhysics::createPrimitiveShape(Primitive shape) 
{
	btScalar x = shape.dimensions[0],
		y = shape.dimensions[1],
		z = shape.dimensions[2];

	switch(shape.shape) {
	case SHAPE_SPHERE:
		return new btSphereShape(x);
	case SHAPE_BOX:
		return new btBoxShape(btVector3(
			btScalar(x/2.0),
			btScalar(y/2.0),
			btScalar(z/2.0)));
	case SHAPE_CYLINDER:
		if(z == 0.0) {
			z = x;
		}

		x /= 2.0;
		y /= 2.0;
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
	case SHAPE_CAPSULE:
		switch(shape.axis) {
		case AXIS_X:
			return new btCapsuleShapeX(x,y);
		case AXIS_Y:
			return new btCapsuleShape(x,y);
		case AXIS_Z:
			return new btCapsuleShapeZ(x,y);
		}
	case SHAPE_CONE:
		switch(shape.axis) {
		case AXIS_X:
			return new btConeShapeX(x,y);
		case AXIS_Y:
			return new btConeShape(x,y);
		case AXIS_Z:
			return new btConeShapeZ(x,y);
		}
	case SHAPE_PLANE:
		switch(shape.axis) {
		case AXIS_X:
			return new btStaticPlaneShape(btVector3(1,0,0), z);
		case AXIS_Y:
			return new btStaticPlaneShape(btVector3(0,1,0), z);
		case AXIS_Z:
			return new btStaticPlaneShape(btVector3(0,0,1), z);
		}
	default:
		return new btEmptyShape;
	}

}

u32 CBulletPhysics::addShape(IModel* model)
{
	if(model->primitives.size() > 0) {
		btCompoundShape* compound = new btCompoundShape();
	
		for(auto it = model->primitives.begin(); it != model->primitives.end(); it++) {
			Primitive primitive = *it;
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
