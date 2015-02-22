include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

# Includes and objects
Objects = EntityManager.o EventManager.o SimplePathfinder.o World.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_GAME -D HR_MODULE_AI

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgame.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
