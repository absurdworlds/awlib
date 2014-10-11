
SetupProject( "hrcore", 
	"stringutils.cpp",
	"CSettingsManager.cpp", "CSettingsManager.h",
	"CModelLoader.cpp", "CModelLoader.h",
	"CLogger.cpp", "CLogger.h",
	"CHrenginShell.cpp", "CHrenginShell.h",
	"CHDFParser.cpp", "CHDFParser.h",
	"CFileSystem.cpp", "CFileSystem.h");

SetupDefines( "hrcore", "Release",
	"HRENGIN_CORE");
SetupDefines( "hrcore", "Debug",
	"HRENGIN_CORE");

