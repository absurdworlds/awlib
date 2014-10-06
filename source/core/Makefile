# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = stringutils.o CSettingsManager.o CModelLoader.o CLogger.o CHrenginShell.o CHDFParser.o CFileSystem.o

Includes = -I../../include $(ExternalIncludes)

Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes) $(Libraries)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrcore.so
SharedLibFullName = $(SharedLibName).$(Version)


shrared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName)

all: shared

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
