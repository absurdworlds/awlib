/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_log_provider_h
#define aw_log_log_provider_h
#include <aw/log/log.h>
namespace aw {
inline namespace v1 {
#if defined(AW_DISABLE_LOGGER)
constexpr bool disable_logger = true;
#else
constexpr bool disable_logger = false;
#endif

/*!
 * log_provider serves as (global) access point to logger,
 * and decoupling user code from it actual location of the logger.
 */
struct log_provider {
	void set_logger(log* logger)
	{
		this->logger = logger;
	}

	/*!
	 * \{
	 * \see log::message()
	 */
	void message(log::level lvl, string_view src, string_view msg)
	{
		if (disable_logger) return;
		if (logger)
			logger->message(lvl, src, msg);
	}

	void info(string_view src, string_view msg)
	{
		message(log::info, src, msg);
	}

	void warning(string_view src, string_view msg)
	{
		message(log::warning, src, msg);
	}

	void error(string_view src, string_view msg)
	{
		message(log::error, src, msg);
	}

	void fatal(string_view src, string_view msg)
	{
		message(log::critical, src, msg);
	}

	/*! \} */

private:
	log* logger = nullptr;
};
} // namespace log
} // namespace aw
#endif//aw_log_log_provider_h
