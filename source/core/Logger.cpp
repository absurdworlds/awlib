/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "Logger.h"

namespace awrts {
namespace core {

Logger* createLogger()
{
	return new impl_::Logger();
}

namespace impl_ {
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::push(std::string const& msg, LogLevel logLevel)
{
	for(auto it = logs_.begin(); it != logs_.end(); ++it) {
		(*it)->log(msg, logLevel);
	}
}

void Logger::registerLog(LogBook* log)
{
	logs_.push_back(log);
}

void Logger::unregisterLog(LogBook* log)
{
	auto found = std::find(logs.begin(), logs.end(), log);

	if(found != logs.end()) {
		// erase
	}
}
} // namespace impl_
} // namespace core
} // namespace awrts
