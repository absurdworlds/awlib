/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Renderable_
#define _aw_Renderable_

namespace aw {
namespace video {

class Renderable {
public:
	virtual void render() = 0;

};


} // namespace video
} // namespace aw
#endif//_aw_Renderable_
