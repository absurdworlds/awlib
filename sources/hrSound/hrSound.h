// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HRSOUND_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HRSOUND_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HRSOUND_EXPORTS
#define HRSOUND_API __declspec(dllexport)
#else
#define HRSOUND_API __declspec(dllimport)
#endif

// This class is exported from the hrSound.dll
class HRSOUND_API ChrSound {
public:
	ChrSound(void);
	// TODO: add your methods here.
};

extern HRSOUND_API int nhrSound;

HRSOUND_API int fnhrSound(void);
