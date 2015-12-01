/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Path_
#define _aw_Path_

#include <vector>
#include <limits>

#include <aw/common/types.h>
#include <aw/math/Vector3d.h>

namespace aw {
namespace ai {
//! Path consisting of waypoints, which are positions in 3d space
class Path {
public:
	typedef Vector3d<f32> node_type;
	typedef std::vector<node_type> container_type;

	//! Get current node
	node_type getCurrentNode() const
	{
		return nodes_[current_];
	}

	//! Get next node and increment counter
	node_type getNextNode()
	{
		if(current_ < size()) {
			++current_;
		}
		return nodes_[current_];
	}

	//! Get previous node and decrement counter
	node_type getPreviousNode()
	{
		if(current_ < size()) {
			--current_;
		}
		return nodes_[current_];
	}

	//! Get first node
	node_type getFirstNode() const
	{
		return nodes_[0];
	}

	//! Get last node
	node_type getLastNode() const
	{
		return nodes_.back();
	}

	//! Add node to the end
	void addNode(node_type const& node)
	{
		nodes_.push_back(node);
	}

	//! Get current position
	size_t position () const
	{
		return current_;
	}

	//! Check if currently at end of the path
	size_t atEnd() const
	{
		return current_ == size();
	}

	//! Random access
	node_type operator [] (size_t id) const
	{
		return nodes_[id];
	}

	//! Count of nodes in path
	size_t size() const
	{
		return nodes_.size();
	}

	void clear()
	{
		nodes_.clear();
	}

	class iterator
		: public std::iterator<std::random_access_iterator_tag,
			node_type> {
	public:
		iterator(pointer ptr) : ptr_(ptr)
		{
		}

		iterator operator ++ ()
		{
			iterator i = *this;
			ptr_++;
			return i;
		}

		iterator operator ++ (int)
		{
			ptr_++;
			return *this;
		}

		iterator operator -- ()
		{
			iterator i = *this;
			-- ptr_;
			return i;
		}

		iterator operator -- (int)
		{
			-- ptr_;
			return *this;
		}

		reference operator * ()
		{
			return *ptr_;
		}

		pointer operator -> ()
		{
			return ptr_;
		}

		bool operator == (const iterator& other)
		{
			return ptr_ == other.ptr_;
		}

		bool operator != (const iterator& other)
		{
			return ptr_ != other.ptr_;
		}

	private:
		pointer ptr_;
	};


	class const_iterator 
		: public std::iterator<std::random_access_iterator_tag,
			const node_type> {
	public:
		const_iterator(pointer ptr) : ptr_(ptr)
		{
		}

		const_iterator operator ++ ()
		{
			const_iterator i = *this;
			++ ptr_;
			return i;
		}

		const_iterator operator ++ (int)
		{
			++ ptr_;
			return *this;
		}

		const_iterator operator -- ()
		{
			const_iterator i = *this;
			-- ptr_;
			return i;
		}

		const_iterator operator -- (int)
		{
			-- ptr_;
			return *this;
		}

		reference operator * ()
		{
			return *ptr_;
		}

		pointer operator -> ()
		{
			return ptr_;
		}

		bool operator == (const const_iterator& other)
		{
			return ptr_ == other.ptr_;
		}

		bool operator != (const const_iterator& other)
		{
			return ptr_ != other.ptr_;
		}

	private:
		pointer ptr_;
	};

	const_iterator begin() const
	{
		const node_type* node = nodes_.data();
		return const_iterator(node);
	}

	const_iterator end() const
	{
		const node_type* node = nodes_.data() + (nodes_.end() - nodes_.begin());
		return const_iterator(node);
	}

	Path()
		: current_(0)
	{

	}
private:
	container_type nodes_;
	size_t current_;
};

Path::const_iterator findClosestNode(Path::const_iterator& first,
	Path::const_iterator& last, Vector3d<f32> point);

} // namespace ai
} // namespace aw
#endif//_aw_Path_
