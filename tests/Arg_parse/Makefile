include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes =
ExternalLibraries = -Wl,-rpath-link,../../lib,-R,'$$ORIGIN/../lib'

# Includes and objects
Objects = Arg_parse.o
Includes = -I../../include
Libraries = -L../../lib -lhrplatform -lhdf -lhrcore $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = arg_parse
Executable = 1

include ../shared.makefile
