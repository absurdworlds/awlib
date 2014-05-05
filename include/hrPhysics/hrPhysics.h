// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HRPHYSICS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HRPHYSICS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HRPHYSICS_EXPORTS
#define HRPHYSICS_API __declspec(dllexport)
#else
#define HRPHYSICS_API __declspec(dllimport)
#endif

// This class is exported from the hrPhysics.dll
class HRPHYSICS_API ChrPhysics {
public:
	ChrPhysics(void);
	// TODO: add your methods here.
};

extern HRPHYSICS_API int nhrPhysics;

HRPHYSICS_API int fnhrPhysics(void);
