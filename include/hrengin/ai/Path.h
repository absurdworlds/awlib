/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CPath_
#define _hrengin_CPath_

#include <vector>
#include <limits>

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

/* Class representing a path, consisting of points in space */
class Path {
public:
	typedef Vector3d<f32> node_type;
	typedef std::vector<node_type> container_type;

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

	node_type operator [] (size_t id) const
	{
		return nodes_[id];
	}
	
	void push_back(node_type&& node)
	{
		nodes_.push_back(node);
		//return end();
	}

	void clear()
	{
		nodes_.clear();
	}

	Path()
	{
	
	}
private:
	container_type nodes_;
};

Path::const_iterator findClosestNode(Path::const_iterator& first,
	Path::const_iterator& last, Vector3d<f32> point)
{
	f32 closestDistance = std::numeric_limits<f32>::max();
	Path::const_iterator closest = first;

	for(auto it = first; it != last; ++ it) {
		f32 diff = (*it - point).squareLength();

		if(diff < closestDistance) {
			closestDistance = diff;
			closest = it;
		} else if(closestDistance < diff) {
			return -- it;
		}
	}

	return closest;
}

} // namespace ai
} // namespace hrengin

#endif//_hrengin_CPath_
