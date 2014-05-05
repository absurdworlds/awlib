
#include "hrgGlobal.h"
#include "hrcGraphicsCore.h"
#include "hrcModel.h"
#include "Irr.h"

namespace hrengin
{
namespace graphics
{
	
hrcModel::hrcModel(hriGraphicsCore* gcore)
{
	hrcModel(gcore, irr::io::path(modelpath + "default.hmd"));
}

hrcModel::hrcModel(hriGraphicsCore* gcore, irr::io::path modelname) : GCore(gcore)
{
	irr::scene::ISceneManager* scnmgr = gcore->GetSceneManager();
	mesh = scnmgr->getMesh(modelpath + modelname);

	if (!mesh)
	{
		// some error
		fprintf(stderr, "Error: Cannot load mesh\n");
		return;
	}
	
	//irr::scene::IMeshSceneNode* Nodeoutine = scnmgr->addMeshSceneNode( createToonOutlineMesh(scnmgr, mesh->getMesh(0), 0.1, irr::video::SColor(255,255,0,0) ));

	irr::scene::IAnimatedMeshSceneNode* Nodeoutine = scnmgr->addAnimatedMeshSceneNode( scnmgr->getMesh(modelpath + modelname + ".selection.obj"));

    //Nodeoutine->getMaterial(0).DiffuseColor.set(0,0,0,0);
    //Nodeoutine->getMaterial(0).AmbientColor.set(0,0,0,0);
	//Nodeoutine->getMaterial(0).SpecularColor.set(0,0,0,0);
	//Nodeoutine->getMaterial(0).EmissiveColor.set(255,255,0,0);
	//Nodeoutine->setMaterialFlag(irr::video::EMF_WIREFRAME, true)
	Nodeoutine->setMaterialTexture( 0, scnmgr->getVideoDriver()->getTexture("teal") );
	Nodeoutine->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	Nodeoutine->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    Nodeoutine->setMaterialFlag(irr::video::EMF_FRONT_FACE_CULLING, true);

	node = scnmgr->addAnimatedMeshSceneNode( mesh );

	node->setPosition(irr::core::vector3df(0,0.835,0));
	Nodeoutine->setPosition(irr::core::vector3df(0,0.835,0));
	fprintf(stderr, "VE\n");

}

hrcModel::~hrcModel()
{
	mesh->drop();
	node->remove();
}

} //namespace graphics
}