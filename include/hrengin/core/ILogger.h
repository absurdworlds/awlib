#ifndef _hrengin_ILogger_
#define _hrengin_ILogger_

#include <string>
#include <thread>

#include <hrengin/common/config.h>
#include <hrengin/common/api.h>
#include <hrengin/common/macro.h>


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

class ILogBook {
public:
	virtual void log(std::string) = 0;
};

class ILogger {
public:
	virtual ~ILogger() {};
	virtual void push(std::string msg) = 0;
	virtual void addLog(ILogBook* log) = 0;
	
	const std::string endl = std::string("\n");
};

HR_CORE_API ILogger* createLogger();

} // namespace hrengin


#endif//_hrengin_ILogger_