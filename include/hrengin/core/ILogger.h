/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ILogger_
#define _hrengin_ILogger_

#include <string>
#include <thread>

#include <hrengin/common/config.h>
#include <hrengin/common/macro.h>

#include <hrengin/core/api.h>

#define TRACE_FUNCTION() \
do { \
	hrengin::getLogger().push("DEBUG:"); \
	hrengin::getLogger().push(__FUNC__); \
	hrengin::getLogger().push(hrengin::endl); \
} while (0);

#define PUSHMSG(msg) hrengin::getLogger().push(msg);

#define TRACE(...) \
do { \
	hrengin::getLogger().push("TRACE:"); \
	hrengin::getLogger().push(__FILE__  "::" TO_STR(__LINE__) ":"); \
	FOR_EACH(PUSHMSG,__VA_ARGS__) \
	hrengin::getLogger().push(hrengin::endl); \
} while (0);

#undef TRACE
#undef TRACE_FUNCTION

#define TRACE(...)
#define TRACE_FUNCTION(...)

namespace hrengin {

//! Interface for logger output
class ILogBook {
public:
	virtual void log(std::string) = 0;
};

//! Interface for logger class, which is used to write messages into log books
class ILogger {
public:
	//! Virtual destructor
	virtual ~ILogger()
	{
	}

	virtual void push(std::string msg) = 0;
	virtual void addLog(ILogBook* log) = 0;
	
	const std::string endl = std::string("\n");
};

HR_CORE_API ILogger* createLogger();

} // namespace hrengin

#endif//_hrengin_ILogger_
