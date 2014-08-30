#ifndef _hrengin_IRenderingDevice_
#define _hrengin_IRenderingDevice_

#include <hrengin/common/Vector3d.h>
/* yt6dew — I don't know what is that, propbably someone was playng with
 keyboard. I decided to keep it.
 */

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
	
	/* temporary */
	virtual void drawDebug() = 0;


	virtual bool drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib) = 0;
	virtual void drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color) = 0;
};

	
} // namespace video
} // namespace hrengin

#endif//_hrengin_IRenderingDevice_