# Add paths to dependency headers here
ExternalIncludes = -I../dependencies/include/
ExternalLibraries = -Wl,-rpath-link,./,-R../../dependencies/lib,-R.

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CGame.o game.o
Includes = -I../../include $(ExternalIncludes)
Libraries = -L../../lib -lhrgame -lhrcore -lhrgraphics -lhrphysics -lhrplatform $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = testgame
Executable = 1

include ../shared.makefile
