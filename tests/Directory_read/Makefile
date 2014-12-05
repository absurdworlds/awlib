# Add paths to dependency headers here
ExternalIncludes = -I../dependencies/include/
ExternalLibraries = -Wl,-R,'$$ORIGIN/../lib'

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = Directory_read.o
Includes = -I../../include
Libraries = -L../../lib -lhrplatform $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = directory_read
Executable = 1

include ../shared.makefile
