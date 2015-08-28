
SetupProject( "hrgraphics", 
	"CameraNode.cpp", "CameraNode.h",
	"ConsoleGUI.cpp", "ConsoleGUI.h",
	"GUIListBox.cpp", "GUIListBox.h",
	"GuiManager.cpp", "GuiManager.h",
	"GUITextBox.cpp", "GUITextBox.h",
	"GUIWindow.cpp", "GUIWindow.h",
	"InputManager.cpp", "InputManager.h",
	"LightNode.cpp", "LightNode.h",
	"RenderingDevice.cpp", "RenderingDevice.h",
	"SceneManager.cpp", "SceneManager.h",
	"VideoManager.cpp", "VideoManager.h",
	"VisNode.cpp", "VisNode.h");

SetupDefines( "hrgraphics", "Release",
	"HRENGIN_GRAPHICS");
SetupDefines( "hrgraphics", "Debug",
	"HRENGIN_GRAPHICS");

