# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -L../../dependencies/lib -lbass


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CSoundManager.o
Includes = -I../../include $(ExternalIncludes)

Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhraudio.so
SharedLibFullName = $(SharedLibName).$(Version)


shrared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName) $(Libraries)

all: shared

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
