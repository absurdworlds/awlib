/* hrEngin


*/

#ifndef __HR_ENGIN_H__
#define __HR_ENGIN_H__

#include "hrConfig.h"

#ifdef HRENGIN_EXPORTS
#define HRENGIN_API __declspec(dllexport)
#else
#define HRENGIN_API __declspec(dllimport)
#endif

#include "hrtype.h"
#include "hriEncore.h"
#include "hriUnit.h"


namespace hrengin
{
	
HRENGIN_API hriEncore* KickstartEngine ();

} // namespace hrengin


#endif //__HR_ENGIN_H__