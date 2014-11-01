# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CEntityManager.o CEventManager.o CSimplePathfinder.o CWorld.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_GAME -D HR_MODULE_AI

# Compiler flags
include ../settings.gmake

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgame.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../targets.gmake
