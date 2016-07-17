/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_MultiLog_h
#define aw_MultiLog_h
#include <vector>
#include <aw/logger/Log.h>
#include <aw/logger/export.h>
namespace aw {
inline namespace log {
/*!
 * MultiLog redirects message to multiple logs.
 */
struct AW_LOG_EXP MultiLog : Log {
	~MultiLog() = default;

	/*!
	 * Sends log to recipients;
	 * \see Log::log()
	 */
	void log(Log::Level level,
	         std::string const& src,
	         std::string const& msg) override;

	/*!
	 * Add a recipient.
	 * Registering recipient multiple times will cause it
	 * to receive multiple copies of messages.
	 *
	 * When deleted, recipient must be removed manually with remove().
	 */
	void add(Log& log)
	{
		recipients.push_back(&log);
	}

	/*!
	 * Remove recipient.
	 */
	void remove(Log& log)
	{
		auto to_erase = std::remove(begin(recipients), end(recipients), &log);
		if (to_erase != end(recipients))
			recipients.erase(to_erase, end(recipients));
	}

private:
	std::vector<Log*> recipients;
};
} // namespace log
} // namespace aw
#endif//aw_MultiLog_h
