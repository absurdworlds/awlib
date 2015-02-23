include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

# Includes and objects
Objects = ArgParser.o MurmurHash3.o \
	  SettingsManager.o HDFSettingsLoader.o ModelLoader.o \
	  FileSystem.o Logger.o HrenginShell.o \
	  string/compose.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_CORE

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrcore.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
