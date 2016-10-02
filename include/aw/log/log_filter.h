/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_filter_h
#define aw_log_filter_h
#include <aw/log/multi_log.h>
#include <functional>
#include <aw/utility/functional/trivial.h>
namespace aw {
inline namespace v1 {
/*!
 * log_filter applies an arbitrary filter to messages,
 * and then redirects them to recipients
 */
struct AW_LOG_EXP log_filter : multi_log {
	using filter_func = bool(string_view);
	using filter = std::function<filter_func>;

	/*!
	 * By default LogFilter matches any message.
	 */
	log_filter() = default;

	/*!
	 * Construct LogFilter with minimum logging level.
	 */
	log_filter(log::level min_level)
		: min_level(min_level)
	{}

	/*!
	 * Construct LogFilter with specified filters.
	 */
	log_filter(filter src, filter msg)
		: src_filter(src), msg_filter(msg)
	{}

	~log_filter() = default;

	/*!
	 * Check for any match of regexes and send message to recipients.
	 * \see log::message()
	 */
	void message(log::level lvl, string_view src, string_view msg) override;

	void set_source_filter(filter fn)
	{
		src_filter = fn;
	}

	void set_message_filter(filter fn)
	{
		msg_filter = fn;
	}

	void set_min_level(log::level level)
	{
		min_level = level;
	}

	log::level get_min_level() const
	{
		return min_level;
	}

private:
	log::level min_level = log::info;
	filter src_filter{ true_func<string_view>{} };
	filter msg_filter{ true_func<string_view>{} };
};
} // namespace v1
} // namespace aw
#endif//aw_LogFilter_h
