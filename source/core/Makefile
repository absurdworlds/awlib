include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

# Includes and objects
Objects = CHDFParser.o CSettingsManager.o CModelLoader.o \
	  CFileSystem.o CLogger.o CHrenginShell.o \
	  CArgParser.o MurmurHash3.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_CORE -D HR_MODULE_HDF

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrcore.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
