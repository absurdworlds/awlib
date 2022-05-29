#pragma once

#include <aw/log/log.h>

#include <aw/types/containers/queue.h>

#include <aw/utility/test.h>
#include <aw/utility/to_string/tuple.h>

#include <tuple>

namespace aw {
template <>
struct string_converter<log::level> {
	log::level level;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		switch (level)
		{
		case log::info:     fmt.convert("info");     break;
		case log::warning:  fmt.convert("warning");  break;
		case log::error:    fmt.convert("error");    break;
		case log::critical: fmt.convert("critical"); break;
		}

		return fmt;
	}
};

struct log_tester : log {
	void message(log::level lvl, string_view src, string_view msg) override
	{
		auto received = std::make_tuple(lvl, src, msg);
		if (expected.empty()) {
			TestFail("Unexpected message: " + to_string(received));
			return;
		}

		if (TestEqual(received, expected.front()))
		{
			expected.pop_front();
		}
	}

	void expect(log::level lvl, string_view src, string_view msg)
	{
		expected.emplace_back(lvl, src, msg);
	}

	queue<std::tuple<log::level, string_view, string_view>> expected;
};
} // namespace aw
