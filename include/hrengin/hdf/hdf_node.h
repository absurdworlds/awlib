/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hdf_node_
#define _hrengin_hdf_node_
#include <vector>
#include <string>
#include <algorithm>

#include <hrengin/common/stringutils.h>
#include <hrengin/core/hdf_value.h>

namespace hrengin {
namespace hdf {

/*!
 * This class is used to represend HDF document structure
 */
class Node {
	typedef std::pair<std::string,Value> key_value_pair;
	typedef std::vector<key_value_pair> value_container;

	typedef std::pair<std::string,Node> key_node_pair;
	typedef std::vector<key_node_pair> node_container;
public:
	/*!
	 * Add child node
	 */
	void addNode(std::string name, Node node)
	{
		key_node_pair subnode(name, node);
		nodes_.push_back(subnode);
	}

	/*!
	 * Get iterator to first child node
	 */
	node_container::iterator nodesBegin()
	{
		return nodes_.begin();
	}

	/*!
	 * Get iterator to the end
	 * \return Iterator to slot past last child node
	 */
	node_container::iterator nodesEnd()
	{
		return nodes_.begin();
	}

	/*!
	 * Find child node by name
	 * \param name Name of the node to search for
	 * \param startAt Point to start the search at
	 * \return iterator to found node
	 */
	node_container::iterator
		findNode(std::string name, node_container::iterator startAt)
	{
		for(auto iter = startAt; iter != nodes_.end(); ++iter) {
			if(iter->first == name) {
				return iter;
			}
		}

		return nodes_.end();
	}

	/*!
	 * Remove child node
	 */
	void removeNode(node_container::iterator node)
	{
		nodes_.erase(node);
	}

	/*!
	 * Get child node by index
	 * \return Child node or an empty node
	 */
	Node getNode(node_container::size_type index)
	{
		if(index < nodes_.size()) {
			return nodes_[index].second;
		}
		return Node();
	}

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
				values_.begin(),
				values_.end(),
				findKey);

		if(found != values_.end()) {
			return false;
		}

		key_value_pair value(name, val);
		values_.push_back(value);
		return true;
	}

	/*!
	 * Find HDF value
	 */
	value_container::iterator
		findValue(std::string name)
	{
		for(auto iter = values_.begin(); iter != values_.end(); ++iter) {
			if(iter->first == name) {
				return iter;
			}
		}

		return values_.end();
	}

	void removeValue(value_container::iterator val)
	{
		values_.erase(val);
	}

	Value getValue(value_container::size_type index)
	{
		if(index < values_.size()) {
			return values_[index].second;
		}

		return Value();
	}
private:
	value_container values_;
	node_container nodes_;
};

//! Used for storage of an arbitary HDF document
class Document : protected Node {
public:
	void addNode(std::string name, Node node)
	{
		Node::addNode(name, node);
	}

	node_container::iterator
		nodesBegin()
	{
		return Node::nodesBegin();
	}

	node_container::iterator
		findNode(std::string name, node_container::iterator startAt)
	{
		return Node::findNode(name, startAt);
	}

	void removeNode(node_container::iterator node)
	{
		Node::removeNode(node);
	}

	Node getNode(node_container::size_type index)
	{
		return Node::getNode(index);
	}
};

} // namespace hdf
} // namespace hrengin
#endif//_hrengin_hdf_node_
