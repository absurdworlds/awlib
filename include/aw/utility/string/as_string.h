/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_string_as_string_h
#define aw_string_as_string_h
#include <string>
#include <aw/types/types.h>
namespace aw {
/*
 * Convert value to string. There may be specializations
 * for other types in their headers.
 */

inline std::string as_string(int value)
{
	return std::to_string(value);
}

inline std::string as_string(long value)
{
	return std::to_string(value);
}

inline std::string as_string(long long value)
{
	return std::to_string(value);
}

inline std::string as_string(unsigned value)
{
	return std::to_string(value);
}

inline std::string as_string(unsigned long value)
{
	return std::to_string(value);
}

inline std::string as_string(unsigned long long value)
{
	return std::to_string(value);
}

inline std::string as_string(float value)
{
 	return std::to_string(value);
}

inline std::string as_string(double value)
{
	return std::to_string(value);
}

inline std::string as_string(long double value)
{
	return std::to_string(value);
}

inline std::string as_string(char const* value)
{
	return std::string(value);
}

inline std::string as_string(std::string value)
{
	return value;
}

template<typename T>
std::string as_string(opt<T> value)
{
	if (value)
		return as_string(value.value());

	return "nullopt";
}

} // namespace aw
#endif//aw_string_as_string_h
