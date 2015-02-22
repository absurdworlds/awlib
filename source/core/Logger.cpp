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

Logger_* createLogger()
{
	return new Logger_();
}

Logger_::Logger_()
{
}

Logger_::~Logger_()
{
}

void Logger_::push(std::string msg)
{
	// woohoo, iterators incompatible
	//for(std::vector<LogBook*>::iterator it; it != logs_.end(); ++it) {
	for(auto it = logs_.begin(); it != logs_.end(); ++it) {
		(*it)->log(msg);
	}
}

void Logger_::addLog(LogBook* log)
{
	logs_.push_back(log);
}
} // namespace core
} // namespace hrengin
