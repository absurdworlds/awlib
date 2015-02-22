/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Logger_
#define _hrengin_Logger_

#include <vector>

#include <hrengin/core/Logger.h>

namespace hrengin {
namespace core {

class LoggerImpl : public Logger {
public:
	LoggerImpl();
	virtual ~LoggerImpl();

	virtual void push(std::string msg);
	virtual void addLog(LogBook* log);
private:
	std::vector<LogBook*> logs_;
};

} // namespace core
} // namespace hrengin
#endif//_hrengin_Logger_
