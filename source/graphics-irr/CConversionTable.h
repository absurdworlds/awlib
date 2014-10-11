/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CConversionTable_
#define _hrengin_CConversionTable_

#include <unordered_map>

namespace irr {
namespace scene {
class ISceneNode;
}
}
namespace hrengin {
namespace scene {
class ISceneNode;

/*! Hack to access irrlicht's scene nodes from public api classes, without
    polluting public api itself.
 */
class CConversionTable {
public:

	void add (void* from, void* to)
	{
		convTable_[from] = to;
	}
	void remove(void* who)
	{
		// don't delete,
		convTable_[who] = 0;
	}

	irr::scene::ISceneNode* convertSceneNode (hrengin::scene::ISceneNode* node)
	{
		void* const addr = node;
		return (irr::scene::ISceneNode*)convTable_[addr];
	}

private:
	std::unordered_map<void*,void*> convTable_;
};

} // namespace scene
} // namespace hrengin

#endif //_hrengin_CConversionTable_
