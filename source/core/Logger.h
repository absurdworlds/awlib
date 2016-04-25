/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Logger_impl_
#define _aw_Logger_impl_
#include <vector>

#include <aw/core/Logger.h>

namespace aw {
namespace core {
namespace impl_ {
// Logger interface, which is used to write messages into log books
class Logger : public core::Logger {
public:
	Logger();
	virtual ~Logger();

	virtual void push(std::string const& msg, LogLevel logLevel);
	//virtual void push(std::string const& msg);

	virtual void registerLog(LogBook* log);
	virtual void unregisterLog(LogBook* log);
private:
	std::vector<LogBook*> logs;
};
} // namespace impl_
} // namespace core
} // namespace aw
#endif//_aw_Logger_impl_
