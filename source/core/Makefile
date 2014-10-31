# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = stringutils.o CSettingsManager.o CModelLoader.o CLogger.o CHrenginShell.o CHDFParser.o CFileSystem.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_CORE -D HR_MODULE_HDF

# Compiler flags
include ../settings.gmake
CompilerSettings = $(CompilerFlags) $(Defines) $(Includes) $(Libraries)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrcore.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../targets.gmake