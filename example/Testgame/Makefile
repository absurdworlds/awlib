# Add paths to dependency headers here
ExternalIncludes = -I../dependencies/include/
ExternalLibraries = -Wl,-rpath-link,./,-R../../dependencies/lib,-R.

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CGame.o game.o
Includes = -I../../include $(ExternalIncludes)
Libraries = -L../../lib -lhrgame -lhrcore -lhrgraphics -lhrphysics -lhrplatform $(ExternalLibraries)
Defines = 

# Compiler settings
include ../settings.gmake
CompilerSettings = $(CompilerFlags) $(Defines) $(Includes) $(Libraries)

Version = $(VersionMajor).$(VersionMinor)
ExecutableName = testgame
Executable = 1

testgame: $(Objects)
	$(CXX) $(Objects) -o $(ExecutableName) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
	cp $(ExecutableName) $(InstallDir)/$(ExecutableName)
all: testgame

include ../targets.gmake
