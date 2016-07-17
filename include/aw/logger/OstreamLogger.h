/*
 * Copyright (C)      2016  Hedede <haddayn@gmail.com>
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_OstreamLogger_h
#define aw_OstreamLogger_h
#include <ostream>
#include <aw/logger/Log.h>
#include <aw/logger/export.h>
namespace aw {
inline namespace log {
/*!
 * Prints log to ostream.
 */
struct AW_LOG_EXP OstreamLogger : Log {
	~OstreamLogger() = default;

	OstreamLogger(std::ostream& stream)
		: stream(stream)
	{}

	/*!
	 * Write message to ostream.
	 * \see Log::log()
	 */
	void log(Log::Level level,
	         std::string const& src,
	         std::string const& msg) override;

private:
	std::ostream& stream;
};
} // namespace core
} // namespace aw
#endif//aw_OstreamLogger_h
