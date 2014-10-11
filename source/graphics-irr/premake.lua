
SetupProject( "hrgraphics", 
	"CCameraNode.cpp", "CCameraNode.h",
	"CConsoleGUI.cpp", "CConsoleGUI.h",
	"CGUIListBox.cpp", "CGUIListBox.h",
	"CGuiManager.cpp", "CGuiManager.h",
	"CGUITextBox.cpp", "CGUITextBox.h",
	"CGUIWindow.cpp", "CGUIWindow.h",
	"CInputManager.cpp", "CInputManager.h",
	"CLightNode.cpp", "CLightNode.h",
	"CRenderingDevice.cpp", "CRenderingDevice.h",
	"CSceneManager.cpp", "CSceneManager.h",
	"CVideoManager.cpp", "CVideoManager.h",
	"CVisNode.cpp", "CVisNode.h");

SetupDefines( "hrgraphics", "Release",
	"HRENGIN_GRAPHICS");
SetupDefines( "hrgraphics", "Debug",
	"HRENGIN_GRAPHICS");

