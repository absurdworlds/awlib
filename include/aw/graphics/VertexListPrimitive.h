/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_VertexListPrimitive_
#define _aw_VertexListPrimitive_

#include <aw/common/types.h>
#include <aw/common/Vector3d.h>
#include <aw/graphics/Renderable.h>

namespace aw {
namespace video {

class VertexListPrimitive : IRenderable {
public:
	// temporary — replace with vertex buffer later
	virtual void addVertex(Vectorf3d pos, u32 idx) = 0;
};

	
} // namespace video
} // namespace aw
#endif//_aw_VertexListPrimitive_
