#include <aw/log/regex_filter.h>
#include <aw/log/log_filter.h>
#include <aw/utility/test.h>
#include <aw/types/containers/queue.h>
#include <tuple>

TestFile("log_filter");

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

Test(regex_filter) {
	using namespace aw;
	log_tester log;
	log_filter filter;

	Setup {
		filter.add(log);

		log.expect(log::info, "main()", "test1");
		log.expect(log::info, "main()", "test2");
		log.expect(log::info, "main()", "test4");
		log.expect(log::info, "main()", "testX");
		log.expect(log::info, "test5()", "starting");
		log.expect(log::info, "test6()", "starting");
		log.expect(log::warning, "main()", "test8");
		log.expect(log::error,   "main()", "test9");
	}


	filter.message(log::info, "main()", "test1");

	filter.set_source_filter(regex_filter{std::regex("main")});
	filter.message(log::info, "main()", "test2");
	filter.message(log::info, "niam()", "test3");

	filter.set_message_filter(regex_filter{std::regex("[a-z]+[0-9]")});
	filter.message(log::info, "main()", "test4");
	filter.message(log::info, "main()", "testX");

	filter.set_message_filter(regex_filter{std::regex("[a-z]+[A-Z]")});
	filter.message(log::info, "main()", "test4");
	filter.message(log::info, "main()", "testX");

	filter.set_source_filter(true_func<std::string const&>{});
	filter.set_message_filter(regex_filter{std::regex{".?"}, std::regex{"annoying_message"}});
	filter.message(log::info, "main()", "annoying_message");
	filter.message(log::info, "test5()", "starting");
	filter.message(log::info, "test5()", "test: annoying_message");
	filter.message(log::info, "test5()", "test: annoying_message");
	filter.message(log::info, "test5()", "test: annoying_message");
	filter.message(log::info, "test5()", "test: annoying_message");
	filter.message(log::info, "test5()", "test: annoying_message");
	filter.message(log::info, "test6()", "starting");
	filter.message(log::info, "test6()", "test: annoying_message");
	filter.message(log::info, "test6()", "test: annoying_message");

	filter.set_min_level(log::warning);
	filter.message(log::info,    "main()", "test7");
	filter.message(log::warning, "main()", "test8");
	filter.message(log::error,   "main()", "test9");

	filter.set_source_filter(false_func<std::string const&>{});
	filter.set_message_filter(false_func<std::string const&>{});
	filter.message(log::error,   "main()", "test10");
	filter.message(log::critical,"main()", "test11");
};
} // namespace aw

RunTests();
