/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <OGRE/OgreRoot.h>

#include "CRenderingDevice.h"

namespace hrengin {
namespace graphics {

CRenderingDevice::CRenderingDevice(Ogre::Root* ogreRoot)
: ogreRoot_(ogreRoot)
{

}

bool CRenderingDevice::drawVertexPrimitive(const IVertexBuffer& vb, const IIndexBuffer& ib)
{
	return false;
}

void CRenderingDevice::drawLine(const Vector3d<f32>& from,
	const Vector3d<f32>& to, const Vector3d<f32>& color)
{


}


bool CRenderingDevice::beginRender()
{
	return ogreRoot_->renderOneFrame();
}

void CRenderingDevice::drawDebug()
{
}

bool CRenderingDevice::endRender()
{
	return true;
	//return ogreRoot_->renderOneFrame();
}

} // namespace video
} // namespace hrengin
