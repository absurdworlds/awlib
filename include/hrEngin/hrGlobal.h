


#ifndef __HR_GLOBAL_H__
#define __HR_GLOBAL_H__

#ifdef HRENGIN_EXPORTS
#define HRENGIN_API __declspec(dllexport)
#else
#define HRENGIN_API __declspec(dllimport)
#endif

#include "hrtype.h"

#endif //__HR_GLOBAL_H__