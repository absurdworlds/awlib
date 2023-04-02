/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_to_string_formatters_pretty_print_h
#define aw_to_string_formatters_pretty_print_h
#include <aw/algorithm/in.h>
#include <aw/utility/string/escape.h>

#include <vector>
namespace aw {
namespace formatter {
struct pretty_print {
	pretty_print() = default;
	pretty_print(pretty_print const&) = default;

	operator std::string() const { return result; }

	void list_start() { result.push_back('{'); stack.emplace_back(); }
	void list_end()   { result.push_back('}'); stack.pop_back(); }

	void compound_start() { list_start(); }
	void compound_end()   { list_end(); }

	pretty_print& literal(string_view lit)
	{
		result.append(lit.data(), lit.size());
		return *this;
	}

	pretty_print& value_separator()
	{
		if (!first_value()) result.append(", ");
		else first_value() = false;
		return *this;
	}

	template<typename T>
	pretty_print& value(T&& val)
	{
		value_separator();
		convert(std::forward<T>(val));
		return *this;
	}

	pretty_print& empty_value()
	{
		value_separator();
		return *this;
	};

	//void convert(signed char val) { result.append(std::to_string(val)); }
	void convert(short val)  { result.append(std::to_string(val)); }
	void convert(int val)  { result.append(std::to_string(val)); }
	void convert(long val) { result.append(std::to_string(val)); }
	void convert(long long val) { result.append(std::to_string(val)); }

	//void convert(unsigned char val) { result.append(std::to_string(val)); }
	void convert(unsigned short val)     { result.append(std::to_string(val)); }
	void convert(unsigned val)           { result.append(std::to_string(val)); }
	void convert(unsigned long val)      { result.append(std::to_string(val)); }
	void convert(unsigned long long val) { result.append(std::to_string(val)); }

	void convert(float val)  { result.append(std::to_string(val)); }
	void convert(double val) { result.append(std::to_string(val)); }
	void convert(long double val) { result.append(std::to_string(val)); }


	void convert(void const* ptr) { convert(uintptr_t(ptr)); }

	void convert(char8_t val) { result.append(std::to_string(val)); }
	void convert(char16_t val) { result.append(std::to_string(val)); }
	void convert(char32_t val) { result.append(std::to_string(val)); }
	void convert(wchar_t val)  { result.append(std::to_string(val)); }

	void convert(char val)
	{
		// TODO: non-printable chars
		if (in_compound())
			add_escaped(val);
		else
			result.push_back(val);
	}

	void convert(string_view val)
	{
		if (in_compound())
			add_escaped(std::string(val));
		else
			result.append(val.data(), val.size());
	}

	void convert(char const* val) { convert(string_view(val)); }
	void convert(std::string const& val) { convert(string_view(val)); }

	template<typename T>
	void convert(T const& val)
	{
		using aw::to_string;
		to_string(val, *this);
	}

private:
	void add_escaped(char c)
	{
		result.push_back('\'');
		if (in(c, '\\', '\''))
			result.push_back('\\');
		result.push_back(c);
		result.push_back('\'');
	}

	void add_escaped(std::string&& s)
	{
		result.push_back('"');
		string::escape_quotes(s, result);
		result.push_back('"');
	}

	std::string result;

	struct state {
		bool first_value = true;
	};
	std::vector<state> stack = {{}};

	bool in_compound() const { return stack.size() > 1; }
	bool& first_value() { return stack.back().first_value; }
};
} // namespace formatter
} // namespace aw
#endif//aw_to_string_formatters_pretty_print_h
