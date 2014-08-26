
#include <Irrlicht/irrlicht.h>

#include "CRenderingDevice.h"



namespace hrengin {
namespace graphics {


bool CRenderingDevice::drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib)
{


}

bool CRenderingDevice::beginRender()
{
	driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
}

bool CRenderingDevice::endRender()
{
	driver->endScene();
}


	
} // namespace video
} // namespace hrengin
