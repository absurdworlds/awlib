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

# Compiler flags
CompilerFlags  = $(Includes)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc -std=c99
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrphysics.so
SharedLibFullName = $(SharedLibName).$(Version)


shared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName) $(Libraries)
	cp $(SharedLibFullName) $(SharedLibName)

all: shared

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
