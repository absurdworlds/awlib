include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes =
ExternalLibraries = -Wl,-rpath-link,../../lib,-R,'$$ORIGIN/../lib'

# Includes and objects
Objects = hpacker.o CStringBank.o \
	  CHPKListWriter.o CHPKHtableWriter.o CHPKTreeWriter.o \
	  CItdReader.o CItdPacker.o
Includes = -I../../include
Libraries = -L../../lib -lhrplatform -lhrcore $(ExternalLibraries)
Defines = 

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = hpacker
Executable = 1

include ../../tests/shared.makefile
