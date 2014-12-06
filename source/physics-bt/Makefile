include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/ -I../../dependencies/include/Bullet/
ExternalLibraries = -L../../dependencies/lib -lBulletCollision -lBulletDynamics

# Includes and objects
Objects = CBulletPhysics.o CCollisionPhantom.o CDebugDrawer.o CPhysicsWorld.o CRigidBody.o hrToBullet.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_PHYSICS

# Binary name
Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrphysics.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
