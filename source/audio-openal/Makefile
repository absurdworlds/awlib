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
Defines = -D HR_MODULE_SOUND

# Compiler flags
include ../settings.gmake
CompilerSettings = $(CompilerFlags) $(Defines) $(Includes) $(Libraries)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhraudio.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../targets.gmake