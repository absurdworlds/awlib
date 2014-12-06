# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -L../../dependencies/lib -lbass

include ../../Makefile

# Includes and objects
Objects = CSoundManager.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_SOUND

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhraudio.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
