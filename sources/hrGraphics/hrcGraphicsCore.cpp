
#include "hrcGraphicsCore.h"
#include "hrcModel.h"
#include "IrrExt/CSceneNodeAnimatorCameraRTS.h"

namespace hrengin
{
namespace graphics
{

hrcGraphicsCore::hrcGraphicsCore(hriEncore* p)
	: parent(p)
{
	/* using only OpenGL, at least at development stage
	irr::video::E_DRIVER_TYPE driver_type;

	switch(gdtype)
	{
		case GD_SOFTWARE:
			driver_type = irr::video::EDT_SOFTWARE;
			break;

		case GD_DIRECT3D9:
			driver_type = irr::video::EDT_DIRECT3D9;
			break;

		case GD_OPENGL:			
			driver_type = irr::video::EDT_OPENGL;
			break;
		default:
			driver_type = irr::video::EDT_NULL;
			break;
	}*/
	
	//device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(dimx, dimy), bitness, fullscreen, false, vsync, 0);
	device = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600), 32, false, false, true, 0);

	/*if (device == 0)
	{
		throw something;
	}*/

	device->setWindowCaption(L"hrEngine - Irrlicht 1.8.1");
	
	driver = device->getVideoDriver();
	scnmgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	CreateScene() ;
};

hrcGraphicsCore::~hrcGraphicsCore() 
{
	device->drop();
};

/*
bool hGraphicsWrapper::Run()
{
	return device->run();
}*/

void hrcGraphicsCore::CreateScene() 
{

	irr::scene::ICameraSceneNode* node = scnmgr->addCameraSceneNode(0, irr::core::vector3df(0,20,30), irr::core::vector3df(0,0,0));
	irr::scene::ISceneNodeAnimatorCameraRTS* animator = new irr::scene::CSceneNodeAnimatorCameraRTS(device->getCursorControl(),device->getTimer()); 
	node->addAnimator(animator);
	animator->drop();
	

	irr::scene::ILightSceneNode* light1 =	scnmgr->addLightSceneNode(0, irr::core::vector3df(100,1000,100), irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);
	irr::scene::IAnimatedMesh* mesh = scnmgr->getMesh(irr::io::path("..\\data\\models\\ground.obj"));

	irr::scene::IAnimatedMeshSceneNode* nodu = scnmgr->addAnimatedMeshSceneNode( mesh );

	irr::video::IImage *teal = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *blue = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	irr::video::IImage *red  = device->getVideoDriver()->createImage(irr::video::ECF_A8R8G8B8, irr::core::dimension2d<irr::u32>(128, 128));
	teal->fill(irr::video::SColor(130, 0, 255, 255));
	blue->fill(irr::video::SColor(130, 0, 0, 255));
	red->fill(irr::video::SColor(64, 255, 0, 0));
	
	device->getVideoDriver()->addTexture("teal", teal);
	device->getVideoDriver()->addTexture("blue", blue);
	device->getVideoDriver()->addTexture("red", red);
}

bool hrcGraphicsCore::Draw()
{
	if(device->run())
	{
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

			scnmgr->drawAll();
			guienv->drawAll();	// TODO: give this to gui:: library

			//TODO: later move t set caption func
			static int lastFPS = -1;
			int fps = driver->getFPS();

			if (lastFPS != fps)  
			{
				irr::core::stringw str = L"hEengin - Irrlicht 1.8.1 DEBUG ["; //later move tosrt caption func
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
			// end todo

			driver->endScene();
		}
		else
		{
			device->yield();
		}

		return true;
	}
	else
	{
		return false;
	}
}

hriModel* hrcGraphicsCore::CreateModel(const char* modelname)//irr::fschar_t* meshname, irr::fschar_t* texture, irr::f32 z, irr::f32 x, irr::f32 y, irr::f32 a)
{
	hriModel* newModel = new hrcModel(this, irr::io::path(modelname));
	


	//node->setPosition(irr::core::vector3df(x,y,z));
	//node->setRotation(irr::core::vector3df(0,a,0));
	
	//fprintf(stderr, "Error: Can load mesh");

	/*if (node)
	{
		//node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setMD2Animation(irr::scene::EMAT_STAND);
		//node->setMaterialTexture( 0, driver->getTexture(texture) );
	}*/

	return newModel;
}

irr::scene::ISceneManager* hrcGraphicsCore::GetSceneManager()
{
	return scnmgr;
}

} // namespace graphics
} // namespace hrengin