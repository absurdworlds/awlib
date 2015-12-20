/*
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_IteratorWrapper_h
#define aw_IteratorWrapper_h
namespace aw {
/*!
 * Helper class to wrap iterator of one type into
 * iterator of another type.
 * Main use is to wrap iterator<std::unique_ptr<T>> into iterator<T>.
 */
template <typename Base, typename T>
class IteratorWrapper :
      public std::iterator<std::random_access_iterator_tag, T> {
public:
	typedef Base base_type;
	typedef IteratorWrapper<Base, T> self_type;

	typedef std::iterator<std::random_access_iterator_tag, T> std_type;
	using typename std_type::reference;
	using typename std_type::pointer;

	IteratorWrapper(base_type base)
		: base(base)
	{}

	reference operator*() const
	{
		return **base;
	}

	pointer operator->() const
	{
		return &(**base);
	}

	self_type& operator++()
	{
		++base;
		return *this;
	}

	self_type& operator--()
	{
		--base;
		return *this;
	}

	bool operator == (self_type const& other)
	{
		return base == other.base;
	}

	bool operator != (self_type const& other)
	{
		return base != other.base;
	}

	bool operator == (base_type const& other)
	{
		return base == other;
	}

	bool operator != (base_type const& other)
	{
		return base != other;
	}
private:
	base_type base;
};
} // namespace aw
#endif//aw_IteratorWrapper_h
