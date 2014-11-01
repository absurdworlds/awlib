# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -L../../dependencies/lib -lIrrlicht

# Version
VersionMajor = 1
VersionMinor = 3

# Includes and objects
IrrExtObjs = IrrExt/CSceneNodeAnimatorCameraRTS.o
Objects = CCameraNode.o CConsoleGUI.o CGUIListBox.o CGuiManager.o CGUITextBox.o CGUIWindow.o CInputManager.o CLightNode.o CRenderingDevice.o CSceneManager.o CVideoManager.o CVisNode.o $(IrrExtObjs)

Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgraphics.so
SharedLibFullName = $(SharedLibName).$(Version)


shared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName) $(Libraries)
	cp $(SharedLibFullName) $(SharedLibName)

all: shared

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)

