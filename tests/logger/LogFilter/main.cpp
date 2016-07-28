/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <aw/logger/OstreamLogger.h>
#include <aw/logger/LogFilter.h>

int main()
{
	using namespace aw;
	OstreamLogger log{std::cout};
	LogFilter filter;

	filter.add(log);

	filter.log(Log::Info, "main()", "test1");

	filter.setSourceFilter(std::regex("main"));
	filter.log(Log::Info, "main()", "test2");
	filter.log(Log::Info, "niam()", "test3");

	filter.setMessageFilter(std::regex("[a-z]+[0-9]"));
	filter.log(Log::Info, "main()", "test4");
	filter.log(Log::Info, "main()", "testX");

	filter.setMessageFilter(std::regex("[a-z]+[A-Z]"));
	filter.log(Log::Info, "main()", "test4");
	filter.log(Log::Info, "main()", "testX");

	filter.setSourceFilter({});
	filter.setMessageFilter({std::regex{".?"}, std::regex{"annoying_message"}});
	filter.log(Log::Info, "main()", "annoying_message");
	filter.log(Log::Info, "test5()", "starting");
	filter.log(Log::Info, "test5()", "test: annoying_message");
	filter.log(Log::Info, "test5()", "test: annoying_message");
	filter.log(Log::Info, "test5()", "test: annoying_message");
	filter.log(Log::Info, "test5()", "test: annoying_message");
	filter.log(Log::Info, "test5()", "test: annoying_message");
	filter.log(Log::Info, "test6()", "starting");
	filter.log(Log::Info, "test6()", "test: annoying_message");
	filter.log(Log::Info, "test6()", "test: annoying_message");

	filter.setMinLevel(Log::Warning);
	filter.log(Log::Info,    "main()", "test7");
	filter.log(Log::Warning, "main()", "test8");
	filter.log(Log::Error,   "main()", "test9");
}
