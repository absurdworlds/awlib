/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_regex_filte_h
#define aw_log_regex_filte_h
#include <aw/types/string_view.h>
#include <aw/log/export.h>
#include <regex>
namespace aw {
inline namespace v1 {
struct AW_LOG_EXP regex_filter {
	/*!
	 * By default Filter inlcudes everything and excludes nothing
	 */
	regex_filter() = default;
	regex_filter(std::regex include)
		: include{include}
	{}
	regex_filter(std::regex include, std::regex exclude)
		: include{include}, exclude{exclude}
	{}

	regex_filter(regex_filter const& other) = default;
	regex_filter(regex_filter&& other) = default;

	regex_filter& operator=(regex_filter const& other) = default;
	regex_filter& operator=(regex_filter&& other) = default;

	bool operator()(string_view msg);

	std::regex include{".?"};
	std::regex exclude{};
};
} // namespace v1
} // namespace aw
#endif//aw_log_regex_filte_h
