#ifndef __HRENGIN_CLogger_H__
#define __HRENGIN_CLogger_H__

#include <string>

#include <hrengin/config/hrConfig.h>

namespace hrengin
{

	class HRENGIN_API CLogger
	{
	public:
		static void init();
		static void log(std::string msg);
		static void exit();
	};

} // namespace hrengin

#endif//__HRENGIN_CLogger_H__
