include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -L../../dependencies/lib -lIrrlicht

# Includes and objects
Objects = CCameraNode.o CConsoleGUI.o CGUIListBox.o CGuiManager.o CGUITextBox.o CGUIWindow.o CInputManager.o CLightNode.o CRenderingDevice.o CSceneManager.o CVideoManager.o CVisNode.o CEntityNode.o 
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_GRAPHICS -D HR_MODULE_GUI -D HR_MODULE_SCENE

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgraphics.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
