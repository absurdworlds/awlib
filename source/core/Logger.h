/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_Logger_impl_
#define _hrengin_Logger_impl_
#include <vector>

#include <hrengin/core/Logger.h>

namespace hrengin {
namespace core {
namespace impl_ {
// Logger interface, which is used to write messages into log books
class Logger : public core::Logger {
public:
	Logger();
	virtual ~Logger();

	virtual void push(std::string msg);
	virtual void addLog(LogBook* log);
private:
	std::vector<LogBook*> logs_;
};
} // namespace impl_
} // namespace core
} // namespace hrengin
#endif//_hrengin_Logger_impl_
