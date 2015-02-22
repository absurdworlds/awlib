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

#include <string>
#include <thread>

#include <hrengin/common/config.h>
#include <hrengin/common/macro.h>

#include <hrengin/core/core.h>

namespace hrengin {
namespace core {
/*!
 * This class provides interface for handling message logs, such as
 * streams and buffers, allowing to output into different targets 
 * simultaneously, e.g. into ingame console and stdout.
 */
class LogBook {
public:
	//! Write logger output
	virtual void log(std::string) = 0;
};

/*!
 * This class provides interface for handling messages,
 * and sending them into different targets, which are
 * represented by LogBook class.
 */ 
class Logger {
	static Logger* globalLogger_;
public:
	//! Set global logger, which is accesset by getGlobalLogger()
	static void setGlobalLogger(Logger* logger)
	{
		globalLogger_ = logger;
	}

	//! Get pointer to global logger, which is set by setGlobalLogger()
	static Logger* getGlobalLogger()
	{
		return globalLogger_;
	}

	//! Virtual destructor
	virtual ~Logger()
	{
	}

	//! Push a message
	virtual void push(std::string msg) = 0;

	//! Add an output to logger
	virtual void addLog(LogBook* log) = 0;

	//! Constant for line ending
	const std::string endl = std::string("\n");
};

//! Create a logger instance
HR_CORE_EXP Logger* createLogger();

} // namespace core
} // namespace hrengin
#endif//_hrengin_Logger_
