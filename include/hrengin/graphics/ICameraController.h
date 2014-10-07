/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ICameraController_
#define _hrengin_ICameraController_

#include <hrengin/graphics/IController.h>

namespace hrengin {
namespace graphics {

//! Class used to control camera movement
class ICameraController : public IController {
public:
	//! Virtual destructor
	virtual ~ICameraController()
	{
	}

	virtual bool update() = 0;

};
	
} // namespace graphics
} // namespace hrengin

#endif//_hrengin_ICameraController_

