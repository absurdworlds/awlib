# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/ -I../../dependencies/include/Bullet/
ExternalLibraries = -L../../dependencies/lib -lBulletCollision -lBulletDynamics


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CBulletPhysics.o CCollisionPhantom.o CDebugDrawer.o CPhysicsWorld.o CRigidBody.o hrToBullet.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_PHYSICS

# Compiler flags
include ../settings.gmake
CompilerSettings = $(CompilerFlags) $(Defines) $(Includes) $(Libraries)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrphysics.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../targets.gmake
