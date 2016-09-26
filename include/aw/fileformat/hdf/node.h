/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_hdf_node_h
#define aw_hdf_node_h
#include <vector>
#include <string>
#include <algorithm>

#include <aw/utility/string/string.h>
#include <aw/fileformat/hdf/Value.h>

namespace aw {
namespace hdf {
template <typename Node, bool strict = false>
struct List : private std::vector<std::pair<std::string, Node>> {
	typedef std::vector<std::pair<std::string, Node>> base;

	using typename base::value_type;
	using typename base::size_type;
	using typename base::iterator;
	using typename base::const_iterator;

	/*!
	 * Add child node
	 */
	bool add(std::string name, Node node)
	{
		if (strict) {
			if(find(name, begin()) != end())
				return false;
		}

		base::emplace_back(name, node);
		return true;
	}

	iterator begin()
	{
		return base::begin();
	}

	iterator end()
	{
		return base::end();
	}

	/*!
	 * Find child node by name
	 * \param name Name of the node to search for
	 * \param startAt Point to start the search at
	 * \return iterator to found node
	 */
	iterator find(std::string name, iterator startAt)
	{
		auto comparator =
		[&name] (value_type const& pair) {
			return (pair.first == name);
		};

		return std::find_if(startAt, base::end(), comparator);
	}

	/*!
	 * Remove child node
	 */
	void remove(iterator node)
	{
		base::erase(node);
	}

	/*!
	 * Get child node by index
	 * \return Child node or an empty node
	 */
	Node get(size_type index)
	{
		if(index > base::size())
			return Node();

		return base::operator[](index).second;
	}
};

/*!
 * This class is used to represend HDF document structure
 */
struct Node : List<Node>, List<Value> {
	auto addNode(std::string name, Node node)
	{
		return List<Node>::add(name, node);
	}
	auto beginNodes()
	{
		return List<Node>::begin();
	}
	auto endNodes()
	{
		return List<Node>::end();
	}
	auto findNode(std::string name, List<Node>::iterator startAt)
	{
		return List<Node>::find(name, startAt);
	}
	auto removeNode(List<Node>::iterator node)
	{
		return List<Node>::remove(node);
	}
	auto getNode(size_t id)
	{
		return List<Node>::get(id);
	}

	auto addValue(std::string name, Value node)
	{
		return List<Value>::add(name, node);
	}
	auto beginValues()
	{
		return List<Value>::begin();
	}
	auto endValues()
	{
		return List<Value>::end();
	}
	auto findValue(std::string name, List<Value>::iterator startAt)
	{
		return List<Value>::find(name, startAt);
	}
	auto removeValue(List<Value>::iterator node)
	{
		return List<Value>::remove(node);
	}
	auto getValue(size_t id)
	{
		return List<Value>::get(id);
	}
};

//! Used for storage of an arbitary HDF document
struct Document : List<Node> {
	auto addNode(std::string name, Node node)
	{
		return List<Node>::add(name, node);
	}
	auto begin()
	{
		return List<Node>::begin();
	}
	auto end()
	{
		return List<Node>::end();
	}
	auto findNode(std::string name, List<Node>::iterator startAt)
	{
		return List<Node>::find(name, startAt);
	}
	auto removeNode(List<Node>::iterator node)
	{
		return List<Node>::remove(node);
	}
	auto getNode(size_t id)
	{
		return List<Node>::get(id);
	}
};
} // namespace hdf
} // namespace aw
#endif//aw_hdf_node_h
