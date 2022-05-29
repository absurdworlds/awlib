/*
 * Copyright (C)      2016  Hedede <haddayn@gmail.com>
 * Copyright (C) 2014-2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_log_h
#define aw_log_log_h
#include <aw/types/string_view.h>
namespace aw {
inline namespace v1 {
/*!
 * Basic logger interface.
 * This interfacce is used by all aw libraries.
 */
class log {
public:
	/*!
	 * Level of importance of the message.
	 */
	enum level {
		info,
		warning,
		error,
		critical
	};

	log() = default;

	log(const log&) = delete;
	log(log&&)      = delete;

	log& operator=(const log&) = delete;
	log& operator=(log&&)      = delete;

	virtual ~log() = default;

	/*!
	 * Write message to log.
	 * \param lvl
	 *    See log::level.
	 * \param src
	 *    Name of the message fource (e.g. `main()`), allows
	 *    implementations to filter messages by source.
	 * \param msg
	 *    Text of the message.
	 */
	virtual void message(level lvl, string_view src, string_view msg) = 0;
};
} // namespace v1
} // namespace aw
#endif//aw_Logger_h
