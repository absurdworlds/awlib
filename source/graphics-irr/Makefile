VersionMajor = 1
VersionMinor = 3

IrrExtObjs = IrrExt/CSceneNodeAnimatorCameraRTS.o
Objects = CCameraNode.o CConsoleGUI.o CGUIListBox.o CGuiManager.o CGUITextBox.o CGUIWindow.o CInputManager.o CLightNode.o CRenderingDevice.o CSceneManager.o CVideoManager.o CVisNode.o $(IrrExtObjs) 

CompilerFlags  = -I../../include -I../../dependencies/include/
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
SharedLibName = libhrgraphics.so
SharedLibFullName = $(SharedLibName).$(Version)



graphics_shrared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName)

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)

