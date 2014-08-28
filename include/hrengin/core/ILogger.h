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

namespace hrengin {

class ILogger
{
public:
	virtual void init() = 0;
	virtual void push(std::string msg) = 0;
	virtual void stop() = 0;
};

const std::string  endl = std::string("\n");

// creates a new logger on heap
HRENGIN_API ILogger& createLogger();

// creates a singleton logger
HRENGIN_API ILogger& getLogger();

} // namespace hrengin


#endif//_hrengin_ILogger_