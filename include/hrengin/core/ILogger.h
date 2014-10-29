/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ILogger_
#define _hrengin_ILogger_

#include <string>
#include <thread>

#include <hrengin/common/config.h>
#include <hrengin/common/macro.h>

#include <hrengin/core/core.h>

namespace hrengin {
namespace core {
//! Interface for logger output
class ILogBook {
public:
	//! Write logger output
	virtual void log (std::string) = 0;
};

//! Logger interface, which is used to write messages into log books
class ILogger {
	static ILogger* globalLogger_;
public:
	//! Set global logger, which is accesset by getGlobalLogger()
	static void setGlobalLogger (ILogger* logger)
	{
		globalLogger_ = logger;
	}

	//! Get pointer to global logger, which is set by setGlobalLogger()
	static ILogger* getGlobalLogger ()
	{
		return globalLogger_;
	}

	//! Virtual destructor
	virtual ~ILogger ()
	{
	}

	//! Push a message
	virtual void push (std::string msg) = 0;

	//! Add an output to logger
	virtual void addLog (ILogBook* log) = 0;
	
	//! Constant for line ending
	const std::string endl = std::string("\n");
};

//! Create a logger instance
HR_CORE_EXP ILogger* createLogger ();

} // namespace core
} // namespace hrengin
#endif//_hrengin_ILogger_
