/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_RenderingDevice_
#define _hrengin_RenderingDevice_

#include <hrengin/graphics/RenderingDevice.h>

namespace irr {
class IrrlichtDevice;

namespace video {
class VideoDriver;

} // namespace video
} // namespace irr

namespace hrengin {
namespace graphics {

class RenderingDevice : public RenderingDevice {
public:
	RenderingDevice(irr::video::IVideoDriver* driver);
	virtual bool drawVertexPrimitive(const VertexBuffer& vb, const IndexBuffer& ib);
	virtual void drawLine(const Vector3d<f32>& from, const Vector3d<f32>& to, const Vector3d<f32>& color);

	virtual bool beginRender();
	virtual void drawDebug();
	virtual bool endRender();
private:
	irr::video::IVideoDriver* driver_;
};

} // namespace graphics
} // namespace hrengin
#endif//_hrengin_RenderingDevice_
