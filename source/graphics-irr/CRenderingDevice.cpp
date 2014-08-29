
#include <Irrlicht/irrlicht.h>

#include "CRenderingDevice.h"



namespace hrengin {
namespace graphics {


bool CRenderingDevice::drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib)
{


}

void CRenderingDevice::drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color)
{
	irr::core::vector3df irrfrom(from.X, from.Y, from.Z);
	irr::core::vector3df irrto(to.X, to.Y, to.Z);
	irr::video::SColor irrcolor(255, (irr::u32)color.X, (irr::u32)color.Y, (irr::u32)color.Z);

	driver->draw3DLine(irrfrom, irrto, irrcolor);
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
