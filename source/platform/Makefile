include ../../Makefile

# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -lsfml-window

# Includes and objects
Objects = CharacterStream.o BufferedStream.o \
	  ReadFile.o WriteFile.o posix/filesystem.o posix/Directory.o \
	  linux/time.o SFML/Window.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_PLATFORM -D HR_MODULE_O

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrplatform.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
