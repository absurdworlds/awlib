/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_LoggerProvider_h
#define aw_LoggerProvider_h
#include <aw/logger/Log.h>
namespace aw {
inline namespace log {
/*!
 * LogProvider serves as (global) access point to logger
 * and decouples code from it's actual location.
 */
struct LogProvider {
	void setLogger(Log* logger)
	{
		this->logger = logger;
	}

	/*!
	 * \see Log::log()
	 */
	void log(Log::Level level, std::string const& src, std::string const& msg)
	{
		if (logger)
			logger->log(level, src, msg);
	}

private:
	Log* logger = nullptr;
};
} // namespace log
} // namespace aw
#endif//aw_LoggerProvider_h
