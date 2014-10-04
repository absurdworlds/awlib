# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CEntityManager.o CEventManager.o CLogger.o CModelLoader.o CSimplePathfinder.o CWorld.o

Includes = -I../../include $(ExternalIncludes)

# Compiler flags
CompilerFlags  = $(Includes)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgame.so
SharedLibFullName = $(SharedLibName).$(Version)


shrared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName)

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
