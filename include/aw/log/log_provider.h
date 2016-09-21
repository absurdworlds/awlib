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
#include <aw/logger/log.h>
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
	void message(log::level lvl, std::string const& src, std::string const& msg)
	{
		if (disable_logger) return;
		if (logger)
			logger->message(lvl, src, msg);
	}

	void info(std::string const& src, std::string const& msg)
	{
		message(log::info, src, msg);
	}

	void warning(std::string const& src, std::string const& msg)
	{
		message(log::warning, src, msg);
	}

	void error(std::string const& src, std::string const& msg)
	{
		message(log::error, src, msg);
	}

	void fatal(std::string const& src, std::string const& msg)
	{
		message(log::fatal, src, msg);
	}

	/*! \} */

private:
	log* logger = nullptr;
};
} // namespace log
} // namespace aw
#endif//aw_log_log_provider_h
