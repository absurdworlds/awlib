#ifndef _hrengin_IDebugDrawer_
#define _hrengin_IDebugDrawer_

//#include <hrengin/graphics/IRenderable.h>

namespace hrengin {

class IBaseEntity;

namespace physics {
	

class IDebugDrawer /*: public IRenderable*/ {
public:
	virtual void render() = 0;
};

	
} // namespace graphics
} // namespace hrengin

#endif //_hrengin_IDebugDrawer_
  