/*
 * Copyright (C) 2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_VertexListPrimitive_
#define _awrts_VertexListPrimitive_

#include <awrts/common/types.h>
#include <awrts/common/Vector3d.h>
#include <awrts/graphics/Renderable.h>

namespace awrts {
namespace video {

class VertexListPrimitive : IRenderable {
public:
	// temporary — replace with vertex buffer later
	virtual void addVertex(Vectorf3d pos, u32 idx) = 0;
};

	
} // namespace video
} // namespace awrts
#endif//_awrts_VertexListPrimitive_
