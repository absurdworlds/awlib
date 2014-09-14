/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
 
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreSceneManager.h>

#include <hrengin/core/hrenginpaths.h>

#include "CCameraNode.h"
#include "CLightNode.h"
#include "CVisNode.h"
#include "CSceneManager.h"


namespace hrengin {
namespace graphics {

CSceneManager::CSceneManager(Ogre::Root* ogreRoot, IRenderingDevice* renderer)
: ogreRoot_(ogreRoot)
{
	scnMgr_ = ogreRoot_->createSceneManager(Ogre::ST_GENERIC);
}

void CSceneManager::createScene()
{
}

void CSceneManager::update()
{

}

//IVisNode* CSceneManager::createMeshSceneNode(IMesh* mesh)
IVisNode* CSceneManager::createMeshSceneNode(const char* meshname)
{
	return 0;
}

ICameraNode* CSceneManager::createCameraSceneNode()
{
	Ogre::Camera* cam = scnMgr_->createCamera("");
	return new CCameraNode(this, cam);
}

ILightNode* CSceneManager::createLightSceneNode()
{
	Ogre::Light* light = scnMgr_->createLight();
	return new CLightNode(this, light);
}

void CSceneManager::drawScene()
{
}

} // namespace graphics
} // namespace hrengin
