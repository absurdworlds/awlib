include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes =
ExternalLibraries = -Wl,-rpath-link,../../lib,-R,'$$ORIGIN/../lib'

# Includes and objects
Objects = hpacker.o CItdFileTree.cpp
Includes = -I../../include
Libraries = -L../../lib -lhrplatform -lhrcore $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = hpacker
Executable = 1

include ../../tests/shared.makefile
