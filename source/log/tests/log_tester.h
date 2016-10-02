#pragma once
#include <aw/types/containers/queue.h>
#include <aw/utility/to_string/tuple.h>
#include <tuple>

namespace aw {
struct log_tester : log {
	void message(log::level lvl, string_view src, string_view msg) override
	{
		auto received = std::make_tuple(lvl, src, msg);
		if (expected.empty()) {
			TestFail("Unexpected message: " + to_string(received));
			return;
		}
		TestAssert(received == expected.front());
		expected.pop_front();
	}

	void expect(log::level lvl, string_view src, string_view msg)
	{
		expected.emplace_back(lvl, src, msg);
	}

	queue<std::tuple<log::level, string_view, string_view>> expected;
};
} // namespace aw
