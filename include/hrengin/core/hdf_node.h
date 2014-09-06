#ifndef _hrengin_hdf_node_
#define _hrengin_hdf_node_

#include <vector>
#include <string>
#include <algorithm>

#include <hrengin/common/stringutils.h>
#include <hrengin/core/hdf_value.h>

namespace hrengin {
namespace hdf {

class Node {
	typedef std::pair<std::string,Value> key_value_pair;
	typedef std::vector<key_value_pair> value_container;

	typedef std::pair<std::string,Node> key_node_pair;
	typedef std::vector<key_node_pair> node_container;
public:
	void addNode(std::string name, Node node)
	{
		key_node_pair subnode(name, node);
		nodes_.push_back(subnode);
	}

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
	
	void removeNode(node_container::iterator node)
	{
		nodes_.erase(node);
	}

	Node getNode(node_container::size_type index)
	{
		if(index < nodes_.size()) {
			return nodes_[index].second;
		}
		return Node();
	}

	bool addValue(std::string name, Value& val)
	{
		auto found = std::find_if(values_.begin(),values_.end(),findKey<Value>(name));

		if(found != values_.end()) {
			return false;
		}

		key_value_pair value(name, val);
		values_.push_back(value);
		return true;
	}
	
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

class Document {
	typedef std::pair<std::string,Node> key_node_pair;
	typedef std::vector<key_node_pair> node_container;
public:
	void addNode(std::string name, Node node)
	{
		key_node_pair subnode(name, node);
		nodes_.push_back(subnode);
	}

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
	
	void removeNode(node_container::iterator node)
	{
		nodes_.erase(node);
	}

	Node getNode(node_container::size_type index)
	{
		if(index < nodes_.size()) {
			return nodes_[index].second;
		}
		return Node();
	}
private:
	node_container nodes_;
};

} // namespace hdf
} // namespace hrengin


#endif//_hrengin_hdf_node_
