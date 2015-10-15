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
class Node;
class NodeList : std::vector<std::pair<std::string, Node>> {
	typedef std::vector<std::pair<std::string, Node>> base;
public:
	using base::value_type;
	using base::size_type;
	using base::iterator;

	/*!
	 * Add child node
	 */
	void addNode(std::string name, Node node)
	{
		base::emplace_back(name, node);
	}

	iterator beginNodes()
	{
		return base::begin();
	}

	iterator endNodes()
	{
		return base::end();
	}

	/*!
	 * Find child node by name
	 * \param name Name of the node to search for
	 * \param startAt Point to start the search at
	 * \return iterator to found node
	 */
	iterator findNode(std::string name, iterator startAt)
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
	void removeNode(iterator node)
	{
		base::erase(node);
	}

	/*!
	 * Get child node by index
	 * \return Child node or an empty node
	 */
	bool getNode(size_type index, Node& out)
	{
		if(index > base::size())
			return false;

		out = base::operator[](index).second;

		return true;
	}
};

class ValueList {
public:
	typedef std::vector<std::pair<std::string, Value>> value_list;

	/*!
	 * Add an HDF value
	 */
	bool addValue(std::string name, Value& val)
	{
		auto findKey = 
		[&name] (std::pair<std::string, Value> const& pair)
		{
			return (pair.first == name);
		};

		auto found = std::find_if(
				values.begin(),
				values.end(),
				findKey);

		if(found != values.end()) {
			return false;
		}

		values.emplace_back(name, val);
		return true;
	}

	/*!
	 * Find HDF value
	 */
	value_list::iterator
		findValue(std::string name)
	{
		for(auto iter = values.begin(); iter != values_.end(); ++iter) {
			if(iter->first == name) {
				return iter;
			}
		}

		return values.end();
	}

	void removeValue(value_list::iterator val)
	{
		values.erase(val);
	}

	Value getValue(value_list::size_type index)
	{
		if(index < values.size())
			return values[index].second;

		return Value();
	}
private:
	value_list values;
};



/*!
 * This class is used to represend HDF document structure
 */
class Node : public NodeList, ValueList {
public:
private:
};

//! Used for storage of an arbitary HDF document
class Document : public NodeList {
public:
};

} // namespace hdf
} // namespace awrts
#endif//_awrts_hdf_node_
