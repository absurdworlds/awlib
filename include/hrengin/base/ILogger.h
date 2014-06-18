#ifndef __HRENGIN_ILogger_H__
#define __HRENGIN_ILogger_H__

#include <string>
#include <thread>

#include <hrengin/config/hrConfig.h>
#include <hrengin/common/hrenginapi.h>

namespace hrengin {

class ILogger
{
public:
	virtual void init() = 0;
	virtual void push(std::string msg) = 0;
	virtual void stop() = 0;
	
	const std::string endl = std::string("\n");
};

// creates a new logger on heap
HRENGIN_API ILogger& createLogger();

// creates a singleton logger
HRENGIN_API ILogger& getLogger();

} // namespace hrengin


#endif//__HRENGIN_ILogger_H__