#ifndef awstd_string_view_h
#define awstd_string_view_h
#include <cassert>
#include <cstddef>
#include <string>
#include <cstring>
#include <algorithm>

#include "../C++/config.h"
#include "type_traits.h"

namespace awstd {
template<size_t N>
inline aw_constexpr size_t stringsize(const char (&array)[N])
{
	size_t n = N;
	while (n && !array[n-1]) --n;
	return n;
}

template <typename T>
struct is_char_pointer { static const bool value = false; };
template <>
struct is_char_pointer<char*> { static const bool value = true; };
template <>
struct is_char_pointer<char const*> { static const bool value = true; };

enum _sfinae { _dummy };

struct string_view {
	static const size_t npos = -1;

	typedef char const*    const_iterator;
	typedef const_iterator iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef const_reverse_iterator reverse_iterator;

	string_view()
		: _data(0), _size(0)
	{}

	template<size_t N>
	string_view(const char (&array)[N])
		: _data(array), _size(stringsize(array))
	{}

	template<typename T>
	string_view(T ptr, typename enable_if<is_char_pointer<T>::value, _sfinae>::type = _dummy)
		: _data(ptr), _size(strlen(ptr))
	{ }


	string_view(char const* ptr, size_t size)
		: _data(ptr), _size(size)
	{ }

	string_view(std::string const& str)
		: _data(str.c_str()), _size(str.size())
	{ }

	string_view(string_view const& str)
		: _data(str.data()), _size(str.size())
	{ }

	string_view& operator=(string_view const& str)
	{
		_data = str.data();
		_size = str.size();
		return *this;
	}

	void swap(string_view& other)
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
	}

	char const* data() const { return _data; }
	size_t size() const { return _size; }

	iterator begin() const { return _data; }
	iterator end() const { return _data + _size; }

	bool empty() const { return begin() == end(); }

	reverse_iterator rbegin() const { return reverse_iterator(end()); }
	reverse_iterator rend() const {   return reverse_iterator(begin()); }

	char operator[](size_t idx) const { return _data[idx]; }

	string_view substr(size_t pos = 0, size_t len = npos) const
	{
		assert(pos <= size());

		len = std::min(len, size() - pos);
		return string_view( data() + pos, len );
	}

	size_t find(string_view str, size_t pos = 0) const
	{
		const size_t len = str.size();

		if (len == 0)
			return (pos < size()) ? pos : npos;

		if (len > size())
			return npos;

		while ( pos <= size() - len ) {
			if (str == substr(pos, len))
				return pos;
			pos = find(str[0], pos+1);
		}

		return npos;
	}

	size_t find(char c, size_t pos = 0) const
	{
		if (pos >= _size)
			return npos;
		iterator beg = begin() + pos;
		iterator it = std::find(beg, end(), c);
		if (it == end())
			return npos;
		return static_cast<size_t>(it - begin());
	}


	size_t rfind(string_view str, size_t pos = npos) const
	{
		const size_t len = str.size();
		if (len == 0)
			return (pos < size()) ? pos : size();
		if (len > size())
			return npos;

		pos = std::min(size() - len, pos) + 1;
		do {
			pos = rfind(str[0], pos - 1);
			if (str == substr(pos, len))
				return pos;

		} while ( pos > 0 );

		return npos;
	}

	size_t rfind(char c, size_t pos = npos) const
	{
		if (empty())
			return npos;

		pos = pos < size() ? pos + 1 : size();

		iterator it = begin() + pos;
		while ( it != begin() ) {
			if (c == *--it)
				return static_cast<size_t>(it - begin());
		}
		return npos;
	}

	size_t find_first_of(string_view str, size_t pos = 0) const
	{
		// meh, doesn't worth it to optimize
		if (pos >= _size || str.empty())
			return npos;
		iterator beg = begin() + pos;
		iterator it = std::find_first_of(beg, end(), str.begin(), str.end());
		if (it == end())
			return npos;
		return static_cast<size_t>(it - begin());
	}

	size_t find_last_of(string_view str, size_t pos = npos) const
	{
		if (empty())
			return npos;

		pos = pos < size() ? pos + 1 : size();

		iterator it = begin() + pos;
		while (it != begin()) {
			iterator it2 = std::find(str.begin(), str.end(), *--it);
			if (it2 != str.end())
				return static_cast<size_t>(it - begin());
		}
		return npos;
	}

	size_t find_first_not_of(string_view str, size_t pos = 0) const
	{
		if (pos >= _size || str.empty())
			return npos;
		iterator it = begin() + pos;
		for (; it != end(); ++it) {
			iterator it2 = std::find(str.begin(), str.end(), *it);
			if (it2 == str.end())
				return static_cast<size_t>(it - begin());
		}
		return npos;
	}

	size_t find_last_not_of(string_view str, size_t pos = npos) const
	{
		if (empty())
			return npos;

		pos = pos < size() ? pos + 1 : size();

		iterator it = begin() + pos;
		while (it != begin()) {
			iterator it2 = std::find(str.begin(), str.end(), *--it);
			if (it2 == str.end())
				return static_cast<size_t>(it - begin());
		}
		return npos;
	}

	void remove_prefix(size_t n)
	{
		assert(n <= size());
		_data += n;
		_size -= n;
	}

	void remove_suffix(size_t n)
	{
		assert(n <= size());
		_size -= n;
	}

	friend bool operator==(string_view a, string_view b)
	{
		if (a.size() != b.size()) return false;
		//return std::equal(a.begin(), a.end(), b.begin()); //undisableable warning
		const_iterator first1 = a.begin();
		const_iterator last1 = a.end();
		const_iterator first2 = b.begin();
		for( ; first1 != last1; ++first1, ++first2 ) {
			if( !(*first1 == *first2) ) {
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(string_view a, string_view b)
	{
		return !(a == b);
	}

	friend bool operator<(string_view a, string_view b)
	{
		return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
	}

	friend bool operator>(string_view a, string_view b)
	{
		return b < a;
	}

	friend bool operator<=(string_view a, string_view b)
	{
		return !(b < a);
	}

	friend bool operator>=(string_view a, string_view b)
	{
		return !(a < b);
	}

	operator std::string() const { return std::string(data(), size()); }

private:
	char const* _data;
	size_t _size;
};

inline std::ostream& operator<<(std::ostream& os, string_view sv)
{
	if (!sv.empty()) os.write(sv.data(), sv.size());
	return os;
}
} // namespace awstd
#endif//awstd_string_view_h
