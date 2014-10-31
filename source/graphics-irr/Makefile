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
Defines = -D HR_MODULE_GRAPHICS -D HR_MODULE_GUI -D HR_MODULE_SCENE

# Compiler flags
include ../settings.gmake
CompilerSettings = $(CompilerFlags) $(Defines) $(Includes) $(Libraries)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgraphics.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../targets.gmake