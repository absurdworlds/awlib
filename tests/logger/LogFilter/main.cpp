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
}
