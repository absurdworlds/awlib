/*
 * Copyright (C) 2026 Hedede <mail@hedede.me>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/log/emscripten_console_logger.h>
#include <aw/string/join.h>
#include "helpers.h"

#include <cstdint>
#include <format>
#include <string>

#include <pthread.h>
#include <emscripten.h>
namespace aw {
inline namespace v1 {
namespace {
int console_method( log::level level )
{
	switch (level) {
		case log::info:     return 0;
		case log::warning:  return 1;
		case log::error:    return 2;
		case log::critical: return 2;
	}
	return 2;
}
} // namespace

void emscripten_console_logger::message(log::level level, string_view src, string_view msg)
{
	const string_view lvl = opts.show_level ? describe(level) : string_view{};

	const auto line = opts.show_thread
		? std::format("{} tid:{:#x}: {}{}",
			src, reinterpret_cast<std::uintptr_t>(pthread_self()), lvl, msg)
		: std::format("{}: {}{}", src, lvl, msg);

	EM_ASM({
		var text = UTF8ToString($0);
		switch ($1) {
		case 0:  console.info(text);  break;
		case 1:  console.warn(text);  break;
		default: console.error(text); break;
		}
	}, line.c_str(), console_method(level));
}
} // namespace v1
} // namespace aw
