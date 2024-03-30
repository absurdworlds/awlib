/*
 * Copyright (C) 2023 Hudd <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_type_name_h
#define aw_utility_type_name_h

#include <aw/utility/string/trim.h>

#include <aw/config.h>

template<typename T>
static constexpr std::string_view aw_type_string()
{
	return AW_FUNCTION_SIGNATURE;
}

namespace aw {
class type_name_helper {
	static constexpr size_t full_size = aw_type_string<void>().size();
	static constexpr size_t name_size = string_view("void").size();
	static constexpr size_t prefix_size = aw_type_string<void>().find("void");
	static constexpr size_t suffix_size = full_size - prefix_size - name_size;

public:
	constexpr static string_view extract_name(string_view str)
	{
		using namespace std::string_view_literals;
		const auto str_size = str.size() - prefix_size - suffix_size;
		auto name = str.substr(prefix_size, str_size);
#if AW_COMPILER == AW_COMPILER_MSVC
		if (name.starts_with("class "sv))
			name.remove_prefix("class "sv.size());
		else if (name.starts_with("struct "sv))
			name.remove_prefix("struct "sv.size());
		else if (name.starts_with("enum "sv))
			name.remove_prefix("enum "sv.size());
#endif
		return aw::string::trim(name, " ");
	}
};

template<typename T>
struct type_name
{
	constexpr static std::string_view name()
	{
		return type_name_helper::extract_name(aw_type_string<T>());
	}

	using type = T;
	constexpr static std::string_view value = name();
};

template<typename T>
constexpr std::string_view type_name_v = type_name<T>::value;

} // namespace aw

#endif // aw_utility_type_name_h
