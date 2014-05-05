// hrSound.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "hrSound.h"


// This is an example of an exported variable
HRSOUND_API int nhrSound=0;

// This is an example of an exported function.
HRSOUND_API int fnhrSound(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see hrSound.h for the class definition
ChrSound::ChrSound()
{
	return;
}
