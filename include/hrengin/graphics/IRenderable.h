/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IRenderable_
#define _hrengin_IRenderable_

namespace hrengin {
namespace video {

class IRenderable {
public:
	virtual void render() = 0;

};

	
} // namespace video
} // namespace hrengin

#endif//_hrengin_IRenderable_
