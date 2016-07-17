/*
 * Copyright (C)      2016  Hedede <haddayn@gmail.com>
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_Logger_h
#define aw_Logger_h
#include <string>
namespace aw {
inline namespace log {
/*!
 * Interface for loggers.
 * All awlibs use this class for logging.
 */
struct Log {
	/*!
	 * Level of importance of the message.
	 */
	enum Level {
		Info,
		Warning,
		Error,
		Critical
	};

	virtual ~Log() = default;

	/*!
	 * Write message to log.
	 * \param level
	 *    \see Log::Level
	 * \param src
	 *    Name of the message fource (e.g. `main()`), allows
	 *    implementations to filter messages by source.
	 * \param msg
	 *    Text of the message.
	 */
	virtual void log(
	        Log::Level level,
	        std::string const& src,
	        std::string const& msg) = 0;
};
} // namespace core
} // namespace aw
#endif//aw_Logger_h
