# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/ -I../../dependencies/include/Bullet/
ExternalLibraries = -LBulletCollision -LBulletDynamics


# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
Objects = CBulletPhysics.o CCollisionPhantom.o CDebugDrawer.o CPhysicsWorld.o CRigidBody.o hrToBullet.o

Includes = -I../../include $(ExternalIncludes)

Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes) $(Libraries)
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
