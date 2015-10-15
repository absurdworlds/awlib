/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_hdf_node_
#define _awrts_hdf_node_
#include <vector>
#include <string>
#include <algorithm>
#include <experimental/optional>

#include <awengine/string/utility.h>
#include <awengine/hdf/Value.h>

namespace awrts {
namespace hdf {
template <typename Node>
class List : std::vector<std::pair<std::string, Node>> {
public:
	typedef std::vector<std::pair<std::string, Node>> base;

	using typename base::value_type;
	using typename base::size_type;
	using typename base::iterator;
	using typename base::const_iterator;

	/*!
	 * Add child node
	 */
	void add(std::string name, Node& node)
	{
		base::emplace_back(name, node);
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
		[&name] (value_type const& pair)
		{
			return (pair.first == name);
		};

		return std::find_if(startAt,
		                    base::end(),
		                    comparator);
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

		return Node();
	}
};

/*!
 * This class is used to represend HDF document structure
 */
class Node : List<Node>, List<Value> {
public:
	auto addNode = List<Node>::add;
	auto beginNodes = List<Node>::begin;
	auto endNodes = List<Node>::end;
	auto findNode = List<Node>::find;
	auto removeNode = List<Node>::remove;
	auto getNode = List<Node>::get;

	auto addValue = List<Node>::add;
	auto beginValues = List<Node>::begin;
	auto endValues = List<Node>::end;
	auto findValue = List<Node>::find;
	auto removeValue = List<Node>::remove;
	auto getValue = List<Node>::get;
private:
};

//! Used for storage of an arbitary HDF document
class Document : public List<Node> {
public:
	auto addNode = List<Node>::add;
	auto beginNodes = List<Node>::begin;
	auto endNodes = List<Node>::end;
	auto findNode = List<Node>::find;
	auto removeNode = List<Node>::remove;
	auto getNode = List<Node>::get;
};

} // namespace hdf
} // namespace awrts
#endif//_awrts_hdf_node_
