/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IController_
#define _hrengin_IController_

namespace hrengin {
namespace graphics {

//! Class used to control scene node behavior
class IController {
public:
	//! Virtual destructor
	virtual ~IController()
	{
	}

	virtual bool update() = 0;
};

} // namespace graphics
} // namespace hrengin
#endif//_hrengin_IController_
