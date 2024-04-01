/*
 * Copyright (C) 2014-2020  absurdworlds
 * Copyright (C)      2020  Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hudf_utility_h
#define aw_hudf_utility_h
#include <aw/hudf/document.h>
#include <aw/hudf/export.h>
#include <aw/io/input_stream.h>
#include <aw/log/log.h>

namespace aw::hudf {
inline namespace v1 {
AW_HUDF_EXP value find_value(io::input_stream& file, string_view name, log* l = nullptr);
AW_HUDF_EXP node  find_node(io::input_stream& file, string_view name, log* l = nullptr);

AW_HUDF_EXP node     parse_node(parser& parser);
AW_HUDF_EXP document parse_file(io::input_stream& file, log* l = nullptr);

template <typename T, size_t N>
inline bool get_numbers(value const& val, T (&out)[N])
{
	const auto convert = [&](auto& vec) {
		size_t n = std::min(vec->size(), N);
		for (size_t i = 0; i < n; ++i)
			out[i] = static_cast<T>((*vec)[i]);
	};
	if( auto vec = val.get<std::vector<double>>() ) {
		convert( vec );
		return true;
	}
	if( auto vec = val.get<std::vector<long>>() ) {
		convert( vec );
		return true;
	}
	return false;
};

} // namespace v1
} // namespace aw::hudf
#endif//aw_hudf_utility_h
