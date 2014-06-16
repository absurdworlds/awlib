#ifndef __HRENGIN_ILogger_H__
#define __HRENGIN_ILogger_H__

#include <string>
#include <thread>

#include <hrengin/config/hrConfig.h>

namespace hrengin {

class ILogger
{
public:
	virtual void init() = 0;
	virtual void push(std::string msg) = 0;
	virtual void stop() = 0;
	
	const std::string endl = std::string("\n");
};

HRENGIN_API ILogger& createLogger();

} // namespace hrengin


#endif//__HRENGIN_ILogger_H__