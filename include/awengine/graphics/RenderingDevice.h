/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_RenderingDevice_
#define _awrts_RenderingDevice_

#include <awrts/math/Vector3d.h>
/* yt6dew — I don't know what is that, propbably someone was playng with
 keyboard. I decided to keep it.
 */
namespace awrts {
namespace graphics {

class VertexBuffer;
class IndexBuffer;

//! Interface for rendering the scene into the window
class RenderingDevice {
public:
	/*! Prepare scene for rendering.
	 *  Must be called before drawing anything.
	 */
	virtual bool beginRender() = 0;
	// beginFrame()

	//! end rendering the scene, and swap the buffers
	virtual bool endRender() = 0;
	// post()
	
	//! temporary tool to render debug drawers
	virtual void drawDebug() = 0;

	//! Draw a primitive using index buffer and vertex buffer
	virtual bool drawVertexPrimitive(VertexBuffer const& vb, IndexBuffer const& ib) = 0;

	//! Draw a line primitive
	virtual void drawLine(Vector3d<f32> const& from,
		Vector3d<f32> const& to, Vector3d<f32> const& color) = 0;
};

} // namespace video
} // namespace awrts
#endif//_awrts_RenderingDevice_
