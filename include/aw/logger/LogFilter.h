/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_LogFilter_h
#define aw_LogFilter_h
#include <regex>
#include <aw/logger/MultiLog.h>
namespace aw {
inline namespace log {
/*!
 * LogFilter redirects messages that match the regex to other log.
 */
struct AW_LOG_EXP LogFilter : MultiLog {
	struct Filter {
		/*!
		 * By default Filter inlcudes everything and excludes nothing
		 */
		Filter() = default;
		Filter(std::regex include)
			: include{include}
		{}
		Filter(std::regex include, std::regex exclude)
			: include{include}, exclude{exclude}
		{}

		Filter(Filter const& other) = default;
		Filter(Filter&& other) = default;

		Filter& operator=(Filter const& other) = default;
		Filter& operator=(Filter&& other) = default;

		bool apply(std::string msg);

		std::regex include{".?"};
		std::regex exclude{};
	};

	/*!
	 * By default LogFilter matches any message.
	 */
	LogFilter() = default;
	LogFilter(Filter src, Filter msg)
		: src_filter(src), msg_filter(msg)
	{}

	~LogFilter() = default;

	/*!
	 * Check for any match of regexes and send message to recipients.
	 * \see Log::log()
	 */
	void log(Log::Level level,
	         std::string const& src,
	         std::string const& msg) override;

	void setSourceFilter(Filter regex)
	{
		src_filter = regex;
	}

	void setMessageFilter(Filter regex)
	{
		msg_filter = regex;
	}

private:
	Filter src_filter;
	Filter msg_filter;
};
} // namespace log
} // namespace aw
#endif//aw_LogFilter_h
