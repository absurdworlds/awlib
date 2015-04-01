include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =

# Includes and objects
Objects = Parser.o 
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_HDF

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhdf.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
