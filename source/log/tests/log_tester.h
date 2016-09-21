#pragma once
#include <aw/types/containers/queue.h>
#include <tuple>

namespace aw {
struct log_tester : log {
	void message(log::level lvl, std::string const& src, std::string const& msg) override
	{
		if (expected.empty()) {
			TestFail("Unexpected message: " + msg);
			return;
		}
		TestAssert(std::make_tuple(lvl, src, msg) == expected.front());
		expected.pop_front();
	}

	void expect(log::level lvl, std::string const& src, std::string const& msg)
	{
		expected.emplace_back(lvl, src, msg);
	}

	queue<std::tuple<log::level, std::string, std::string>> expected;
};
} // namespace aw
