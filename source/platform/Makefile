# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = 

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CCharacterStream.o CBufferedStream.o CReadFile.o linux/time.o posix/CDirectory.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_PLATFORM -D HR_MODULE_IO

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrplatform.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
