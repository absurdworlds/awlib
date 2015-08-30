/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_CameraController_
#define _awrts_CameraController_

#include <awrts/graphics/Controller.h>

namespace awrts {
namespace graphics {
//! Class used to control camera movement
class CameraController : public Controller {
public:
	//! Virtual destructor
	virtual ~CameraController()
	{
	}

	virtual bool update() = 0;

};

} // namespace graphics
} // namespace awrts
#endif//_awrts_CameraController_
