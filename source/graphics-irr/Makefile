include ../../Makefile
# Add paths to dependency headers here
ExternalIncludes = -I../../dependencies/include/
ExternalLibraries = -L../../dependencies/lib -lIrrlicht

# Includes and objects
Objects = CameraNode.o VisNode.o EntityNode.o LightNode.o \
	  ConsoleGUI.o GUIListBox.o GuiManager.o GUITextBox.o GUIWindow.o \
	  InputManager.o RenderingDevice.o SceneManager.o VideoManager.o
Includes = -I../../include $(ExternalIncludes)
Libraries = $(ExternalLibraries)
Defines = -D HR_MODULE_GRAPHICS -D HR_MODULE_GUI -D HR_MODULE_SCENE

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgraphics.so
SharedLibFullName = $(SharedLibName).$(Version)

include ../shared.makefile
