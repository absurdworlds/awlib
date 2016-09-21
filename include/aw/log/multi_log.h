/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_multi_log_h
#define aw_multi_log_h
#include <vector>
#include <algorithm>
#include <aw/log/log.h>
#include <aw/log/export.h>
namespace aw {
inline namespace v1 {
/*!
 * Redirects message to multiple logs.
 */
struct multi_log : log {
	~multi_log() = default;

	/*!
	 * Sends log to recipients;
	 * \see log::message()
	 */
	void message(log::level level,
	         std::string const& src,
	         std::string const& msg) override;

	/*!
	 * Add a recipient.
	 * Registering recipient multiple times will cause it
	 * to receive multiple copies of messages.
	 *
	 * When deleted, recipient must be removed manually with remove().
	 */
	void add(log& inst)
	{
		loggers.push_back(&inst);
	}

	/*!
	 * Remove recipient.
	 */
	void remove(log& inst)
	{
		auto to_erase = std::remove(begin(loggers), end(loggers), &inst);
		if (to_erase != end(loggers))
			loggers.erase(to_erase, end(loggers));
	}

private:
	std::vector<log*> loggers;
};
} // namespace v1
} // namespace aw
#endif//aw_multi_log_h
