/*
 * Copyright (C)      2026  Hedede <mail@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_emscripten_console_logger_h
#define aw_log_emscripten_console_logger_h

#include <aw/log/log.h>
#include <aw/log/export.h>

namespace aw {
inline namespace v1 {
/*!
 * Writes log messages to the browser console
 */
struct AW_LOG_EXP emscripten_console_logger : log {
	struct options {
		//! Prefix every line with the calling thread's id.
		bool show_thread = false;

		//! Spell the level out in the message text.
		bool show_level = false;
	};

	emscripten_console_logger() = default;

	explicit emscripten_console_logger(options opts)
		: opts{opts}
	{}

	void message(log::level level, string_view src, string_view msg) override;

private:
	options opts;
};
} // namespace v1
} // namespace aw
#endif//aw_log_emscripten_console_logger_h
