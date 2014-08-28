#ifndef _hrengin_CPath_
#define _hrengin_CPath_

#include <vector>

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace ai {

class CPath {
public:
	typedef u32 nodeId;

	std::vector<Vector3d> pathData_;
	nodeId current_;

	void increment() 
	{
		current_ ++;
	}

	void operator ++ ()
	{
		increment();
	}

	void operator ++ (int)
	{
		increment();
	}
	
	nodeId current() const
	{
		return current_;
	}

	nodeId start() const
	{
		return 0;
	}

	nodeId end() const
	{
		return pathData_.size() - 1;
	}

	Vector3d node(nodeId id) const
	{
		return pathData_[id];
	}
	
	nodeId add(Vector3d node)
	{
		pathData_.push_back(node);
		return end();
	}

	CPath() : current_(0)
	{
	
	}
};

} // namespace ai
} // namespace hrengin

#endif//_hrengin_CPath_