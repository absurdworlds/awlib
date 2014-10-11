
SetupProject( "hrgame", 
	"CEntityManager.cpp", "CEntityManager.h",
	"CEventManager.cpp", "CEventManager.h",
	"CSimplePathfinder.cpp", "CSimplePathfinder.h",
	"CWorld.cpp", "CWorld.h");

SetupDefines( "hrcore", "Release",
	"HRENGIN_GAME");
SetupDefines( "hrcore", "Debug",
	"HRENGIN_GAME");

