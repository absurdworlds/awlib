/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IDebugDrawer_
#define _hrengin_IDebugDrawer_

//#include <hrengin/graphics/IRenderable.h>

namespace hrengin {
namespace physics {

class IDebugDrawer /*: public IRenderable*/ {
public:
	//virtual void render() = 0;

	// internal implementation details
	class Details;
	
	// for internal use only
	virtual IDebugDrawer::Details* getDetails() = 0;
};


} // namespace graphics
} // namespace hrengin

#endif //_hrengin_IDebugDrawer_
