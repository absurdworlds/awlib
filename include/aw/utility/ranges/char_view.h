/*
 * Copyright (C) 2017  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_ranges_char_view_h
#define aw_ranges_char_view_h
namespace aw {
/*!
 * View object of type T as sequence of characters.
 */
template<typename T>
struct char_view {
	char_view(T& value)
		: value{value}
	{}

	char_view(T& value, size_t index)
		: value{value}, index{index}
	{}

	bool operator==(char_view const& other) const
	{
		return index == other.index;
	}

	bool operator!=(char_view const& other) const
	{
		return index != other.index;
	}

	bool operator<(char_view const& other) const
	{
		return index < other.index;
	}

protected:
	char& get()
	{
		return *reinterpret_cast<char*>(&value);
	}

	char const& get() const
	{
		return *reinterpret_cast<char const*>(&value);
	}

	void advance() { ++index; }

	T& get_value() { return value; }
	T const& get_value() const { return value; }

	T& value;

private:
	size_t index = 0;
};

template<typename T>
struct char_view_iterator : char_view<T const> {
	char_view_iterator(T const& value)
		: char_view<T const>{value}
	{}

	char_view_iterator(T const& value, size_t index)
		: char_view<T const>{value, index}
	{ }

	char_view_iterator begin()
	{
		return {value, 0};
	}

	char_view_iterator end()
	{
		return {value, sizeof(T)};
	}

	char operator*() const
	{
		return get();
	}

	char_view_iterator& operator++()
	{
		advance();
		return *this;
	}

private:
	using char_view<T const>::value;
	using char_view<T const>::get;
	using char_view<T const>::advance;
};

template<typename T>
struct char_edit_iterator : char_view<T> {
	char_edit_iterator(T& value)
		: char_view<T>{value}
	{ }

	char_edit_iterator(T& value, size_t index)
		: char_view<T>{value, index}
	{ }

	char_edit_iterator begin()
	{
		return {value, 0};
	}

	char_edit_iterator end()
	{
		return {value, sizeof(value)};
	}

	char& operator*()
	{
		return get();
	}

	char_edit_iterator& operator++()
	{
		advance();
		return *this;
	}

private:
	using char_view<T>::value;
	using char_view<T>::get;
	using char_view<T>::advance;
};
} // namespace aw
#endif//aw_ranges_char_view_h
