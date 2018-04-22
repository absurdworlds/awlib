#ifndef aw_array_view_h
#define aw_array_view_h
#include <cassert>
#include <cstddef>
#include <string>
#include <algorithm>
#include <initializer_list>
#include <aw/meta/conditional.h>
#include <aw/types/strip.h>
#include <aw/types/traits/is_flat_container.h>

namespace aw {
template<typename T>
struct array_ref {
	using value_type = T;
	using pointer    = T*;
	using reference  = T&;

	using iterator   = T*;
	using reverse_iterator = std::reverse_iterator<iterator>;

	using const_iterator = T const*;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	array_ref() = default;

	template<size_t N>
	constexpr array_ref(T (&array)[N])
		: _data{array}, _size{N}
	{}

	constexpr array_ref(T* ptr, size_t length)
		: _data{ptr}, _size{length}
	{ }

	constexpr array_ref(std::initializer_list<remove_const<T>> list)
		: _data{list.begin()}, _size{list.size()}
	{ }

	template<typename C, typename = enable_if<is_flat_container<C>>>
	constexpr array_ref( C& cont )
		: _data{cont.data()}, _size{cont.size()}
	{ }

	constexpr array_ref& operator=(array_ref const&) = default;

	constexpr void swap(array_ref& other)
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
	}

	constexpr iterator begin() { return _data; }
	constexpr iterator end()   { return _data + _size; }

	constexpr const_iterator begin()  const { return _data; }
	constexpr const_iterator end()    const { return _data + _size; }
	constexpr const_iterator cbegin() const { return begin(); }
	constexpr const_iterator cend()   const { return end(); }

	constexpr auto rbegin() { return reverse_iterator{end()}; }
	constexpr auto rend()   { return reverse_iterator{begin()}; }

	constexpr auto rbegin()  const { return const_reverse_iterator{end()}; }
	constexpr auto rend()    const { return const_reverse_iterator{begin()}; }
	constexpr auto crbegin() const { return rbegin(); }
	constexpr auto crend()   const { return rend(); }

	constexpr size_t size() const { return _size; }
	constexpr bool  empty() const { return begin() == end(); }

	constexpr T& operator[](size_t idx) { return _data[idx]; }
	constexpr T* data()  { return _data; }
	constexpr T& front() { return _data[0]; }
	constexpr T& back()  { return _data[_size]; }

	constexpr T const& operator[](size_t idx) const { return _data[idx]; }
	constexpr T const* data()  const { return _data; }
	constexpr T const& front() const { return _data[0]; }
	constexpr T const& back()  const { return _data[_size]; }

	constexpr array_ref slice(size_t pos, size_t end) const
	{
		assert(end <= size());
		assert(pos <= end);

		return {data() + pos, end - pos};
	}

	constexpr void remove_prefix(size_t n)
	{
		assert(n <= _size);
		_data += n;
		_size -= n;
	}

	constexpr void remove_suffix(size_t n)
	{
		assert(n <= _size);
		_size -= n;
	}

private:
	T* _data     = nullptr;
	size_t _size = 0;
};

template<typename T>
using array_view = array_ref<T const>;

template<typename T>
constexpr void swap(array_ref<T>& a, array_ref<T>& b) { return a.swap(b); }

template<typename T>
constexpr auto begin(array_ref<T>& a)   { return a.begin(); }
template<typename T>
constexpr auto end(array_ref<T>& a)     { return a.end(); }
template<typename T>
constexpr auto rbegin(array_ref<T>& a)  { return a.rbegin(); }
template<typename T>
constexpr auto rend(array_ref<T>& a)    { return a.rend(); }

template<typename T>
constexpr auto begin(array_ref<T> const& a)   { return a.begin(); }
template<typename T>
constexpr auto end(array_ref<T> const& a)     { return a.end(); }
template<typename T>
constexpr auto rbegin(array_ref<T> const& a)  { return a.rbegin(); }
template<typename T>
constexpr auto rend(array_ref<T> const& a)    { return a.rend(); }

template<typename T>
constexpr auto cbegin(array_ref<T> const& a)  { return a.cbegin(); }
template<typename T>
constexpr auto cend(array_ref<T> const& a)    { return a.cend(); }
template<typename T>
constexpr auto crbegin(array_ref<T> const& a) { return a.crbegin(); }
template<typename T>
constexpr auto crend(array_ref<T> const& a)   { return a.crend(); }

template<typename T>
bool operator==(array_ref<T> const& a, array_ref<T> const& b)
{
	if (a.size() != b.size()) return false;
	return std::equal(begin(a), end(a), begin(b));
}

template<typename T>
bool operator!=(array_ref<T> const& a, array_ref<T> const& b)
{
	return !(a == b);
}

template<typename T>
bool operator<(array_ref<T> const& a, array_ref<T> const& b)
{
	return std::lexicographical_compare(begin(a), end(a), begin(b), end(b));
}

template<typename T>
bool operator>(array_ref<T> const& a, array_ref<T> const& b)
{
	return b < a;
}

template<typename T>
bool operator<=(array_ref<T> const& a, array_ref<T> const& b)
{
	return !(b < a);
}

template<typename T>
bool operator>=(array_ref<T> const& a, array_ref<T> const& b)
{
	return !(a < b);
}

} // namespace awstd
#endif//aw_array_view_h
