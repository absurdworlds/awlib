include ../../Makefile

# Add paths to dependency headers here
ExternalIncludes =
ExternalLibraries = -Wl,-rpath-link,./,-R,'$$ORIGIN/../lib'

# Includes and objects
Objects = hdf_example.o
Includes = -I../../include $(ExternalIncludes)
Libraries = -L../../lib -lhrdf $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = hdf_example
Executable = 1

include ../shared.makefile
