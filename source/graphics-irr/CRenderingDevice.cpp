
#include <Irrlicht/irrlicht.h>

#include "CRenderingDevice.h"



namespace hrengin {
namespace graphics {

CRenderingDevice::CRenderingDevice(irr::video::IVideoDriver* driver)
: driver_(driver)
{

}

bool CRenderingDevice::drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib)
{

	return false;
}

void CRenderingDevice::drawLine(const Vector3d& from, const Vector3d& to, const Vector3d& color)
{
	irr::core::vector3df irrfrom(from.X, from.Y, from.Z);
	irr::core::vector3df irrto(to.X, to.Y, to.Z);
	irr::video::SColor irrcolor(255, (irr::u32)color.X, (irr::u32)color.Y, (irr::u32)color.Z);

	driver_->draw3DLine(irrfrom, irrto, irrcolor);
}


bool CRenderingDevice::beginRender()
{
	return driver_->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
}

void CRenderingDevice::drawDebug()
{
	irr::video::SMaterial debugMat;
	debugMat.Lighting = false;

	driver_->setMaterial(debugMat);
	driver_->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix);
}

bool CRenderingDevice::endRender()
{
	return driver_->endScene();
}



	
} // namespace video
} // namespace hrengin
