/*
 * Copyright (C)      2016  Hedede <haddayn@gmail.com>
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_ostream_logger_h
#define aw_log_ostream_logger_h
#include <ostream>
#include <aw/log/log.h>
#include <aw/log/export.h>
namespace aw {
inline namespace v1 {
/*!
 * Prints log to ostream.
 */
struct AW_LOG_EXP ostream_logger : log {
	~ostream_logger() = default;

	ostream_logger(std::ostream& stream)
		: stream{stream}
	{}

	/*!
	 * Write message to ostream.
	 * \see log::log()
	 */
	void message(log::level level,
	         std::string const& src,
	         std::string const& msg) override;
private:
	std::ostream& stream;
};
} // namespace v1
} // namespace aw
#endif//aw_log_ostream_logger_h
