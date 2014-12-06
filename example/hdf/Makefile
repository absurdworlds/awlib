include ../../Makefile

# Add paths to dependency headers here
ExternalIncludes = -I../dependencies/include/
ExternalLibraries = -Wl,-rpath-link,./,-R../../dependencies/lib,-R.

# Includes and objects
Objects = hdf_example.o
Includes = -I../../include $(ExternalIncludes)
Libraries = -L../../lib -lhrcore -lhrgraphics $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = hdf_example
Executable = 1

include ../shared.makefile
