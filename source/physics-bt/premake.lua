
SetupProject( "hrphysics", 
	"CBulletPhysics.cpp", "CBulletPhysics.h",
	"CCollisionPhantom.cpp", "CCollisionPhantom.h",
	"CDebugDrawer.cpp", "CDebugDrawer.h",
	"CPhysicsWorld.cpp", "CPhysicsWorld.h",
	"CRigidBody.cpp", "CRigidBody.h",
	"hrToBullet.cpp", "hrToBullet.h");

SetupDefines( "hrphysics", "Release",
	"HRENGIN_PHYSICS");
SetupDefines( "hrphysics", "Debug",
	"HRENGIN_PHYSICS");

