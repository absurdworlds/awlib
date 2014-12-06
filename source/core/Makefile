# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

include ../../Makefile

# Includes and objects
Objects = CSettingsManager.o CModelLoader.o CLogger.o CHrenginShell.o CHDFParser.o CFileSystem.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_CORE -D HR_MODULE_HDF

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrcore.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
