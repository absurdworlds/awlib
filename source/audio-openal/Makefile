# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/ -I /usr/include/AL
ExternalLibraries =

include ../../Makefile

# Includes and objects
Objects = SoundManager.o Sound.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_SOUND

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhraudio.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
