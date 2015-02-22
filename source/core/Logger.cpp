/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "Logger.h"

namespace hrengin {
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

void Logger::push(std::string msg)
{
	// woohoo, iterators incompatible
	//for(std::vector<LogBook*>::iterator it; it != logs_.end(); ++it) {
	for(auto it = logs_.begin(); it != logs_.end(); ++it) {
		(*it)->log(msg);
	}
}

void Logger::addLog(LogBook* log)
{
	logs_.push_back(log);
}
} // namespace impl_
} // namespace core
} // namespace hrengin
