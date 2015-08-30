/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <string>

#include <awrts/scene/IVisNode.h>

#include "game.h"

namespace awrts {
namespace example {

i32 start (std::string)
{
	CGame game;
	bool run = true;
	
	scene::ISceneManager* smgr = game.getSceneManager();
	
	smgr->createLightSceneNode();
	smgr->createCameraSceneNode();
	scene::IVisNode* mesh1 = smgr->createMeshSceneNode("crate10x10.3DS");
	scene::IVisNode* mesh2 = smgr->createMeshSceneNode("crate10x10.3DS");
	mesh2->setParent(mesh1);
	mesh2->setPosition(0,0,45);
	mesh1->setPosition(0,5,0);
	mesh1->setRotation(Vector3d<f32>(0,100,0));


	do {
		run = game.frame();
	} while (run);

	return 0;
}

} // namespace example
} // namespace awrts

//! Collect arguments into string
std::string collect (unsigned int c, char** v)
{
	if (c < 2) {
		return "";
	}
	
	std::string result(v[1]);

	for (int i = 2; i < c; ++i) {
		result += " ";
		result += v[i];
	}

	return result;
}

//! Testgame entry point
int main (int c, char** v)
{
	int err = -1;
	std::string arguments = collect(c, v);

	err = awrts::example::start(arguments);
	return 0;
}
