#ifndef _hrengin_IRenderingDevice_
#define _hrengin_IRenderingDevice_

namespace hrengin {
namespace graphics {

class IVertexBuffer;
class IIndexBuffer;

class IRenderingDevice {
public:
	/* begin rendering the scene, must be called before drawing anything */
	virtual bool beginRender() = 0;

	/* end rendering the scene, */
	virtual bool endRender() = 0;


	virtual bool drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib) = 0;

};

	
} // namespace video
} // namespace hrengin

#endif//_hrengin_IRenderingDevice_