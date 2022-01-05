/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_doc_node_h
#define aw_fileformat_doc_node_h
#include <iosfwd>
#include <string>
#include <algorithm>
#include <aw/types/string_view.h>
#include <aw/types/array_view.h>
#include <aw/doc/value.h>
namespace aw::doc {
inline namespace v1 {
struct parser;

template<typename T>
struct list : private std::vector<T> {
	using base_type = std::vector<T>;

	using iterator       = typename base_type::iterator;
	using const_iterator = typename base_type::const_iterator;
	using value_type     = typename base_type::value_type;

	using base_type::begin;
	using base_type::end;

	using base_type::cbegin;
	using base_type::cend;

	using base_type::empty;
	using base_type::size;

	const T* const_find(string_view name) const
	{
		auto compare_name = [name] (value_type const& pair) {
			return pair.name == name;
		};

		auto it = std::find_if(begin(), end(), compare_name);
		if (it == end())
			return nullptr;
		return &*it;
	}

	const T* find(string_view name) const
	{
		return const_find(name);
	}

	T* find(string_view name)
	{
		return const_cast<T*>(const_find(name));
	}

	void add(T const& node)
	{
		base_type::emplace_back(node);
	}

	array_view<value_type> view() const { return *static_cast<base_type const*>(this); }
};

struct node {
	using iterator = list<node>::iterator;
	using const_iterator = list<node>::const_iterator;

	node* find_child(string_view name)
	{
		return children.find(name);
	}

	const node* find_child(string_view name) const
	{
		return children.const_find(name);
	}

	/*!
	 * Get the value of this node.
	 */
	template<typename T>
	T try_get(T def) const
	{
		return value.try_get(def);
	}

	/*!
	 * Get the value of a child node with name \a name.
	 */
	template<typename T>
	T try_get(string_view name, T def) const
	{
		if (auto* node = find_child(name))
			return node->try_get(def);
		return def;
	}

	/*!
	 * For compatibility with std containers.
	 */
	bool empty() const { return is_empty(); }

	bool is_empty() const
	{
		return children.empty();
	}

	std::string name;
	doc::value  value;
	list<node>  children;
};
} // inline namespace v1
} // namespace aw::doc
#endif//aw_fileformat_doc_node_h
