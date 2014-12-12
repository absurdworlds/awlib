include ../../Makefile

# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = 

# Includes and objects
Objects = posix/filesystem.o posix/CDirectory.o \
	  linux/time.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_PLATFORM -D HR_MODULE_IO

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrplatform.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
