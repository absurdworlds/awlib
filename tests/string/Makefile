include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes =
ExternalLibraries = -Wl,-rpath-link,../../lib,-R,'$$ORIGIN/../lib'

# Includes and objects
Objects = compose_test.o
Includes = -I../../include
Libraries = -L../../lib -lhrplatform -lhdf -lhrcore $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = string_compose
Executable = 1

include ../shared.makefile
