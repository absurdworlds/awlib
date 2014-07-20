#ifndef __HRENGIN_CLogger_H__
#define __HRENGIN_CLogger_H__

#include <thread>
#include <mutex>
#include <string>
#include <deque>

#include <hrengin/core/ILogger.h>

namespace hrengin {

class CLogger : public ILogger
{
public:
	CLogger();
	virtual ~CLogger();
	virtual void init();
	virtual void push(std::string msg);
	virtual void stop();
private:
	virtual void log();
	virtual void write(std::string msg);

	std::deque<std::string> msgQueue_;
	
	std::mutex mutex_;
	std::thread thread_;
	bool stopped_ = false;
	bool finished_ = false;
};

} // namespace hrengin

#endif//__HRENGIN_CLogger_H__