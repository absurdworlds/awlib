# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries =


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CSoundManager.o CSound.o

Includes = -I../../include $(ExternalIncludes)

Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes) $(Libraries)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhraudio.so
SharedLibFullName = $(SharedLibName).$(Version)


shrared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName)

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
