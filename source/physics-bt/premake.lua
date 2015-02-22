
SetupProject( "hrphysics", 
	"BulletPhysics.cpp", "BulletPhysics.h",
	"CollisionPhantom.cpp", "CollisionPhantom.h",
	"DebugDrawer.cpp", "DebugDrawer.h",
	"PhysicsWorld.cpp", "PhysicsWorld.h",
	"RigidBody.cpp", "RigidBody.h",
	"hrToBullet.cpp", "hrToBullet.h");

SetupDefines( "hrphysics", "Release",
	"HRENGIN_PHYSICS");
SetupDefines( "hrphysics", "Debug",
	"HRENGIN_PHYSICS");

