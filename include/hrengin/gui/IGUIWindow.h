/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IGUIWindow_
#define _hrengin_IGUIWindow_

#include <hrengin/gui/IGUIElement.h>

namespace hrengin {
namespace gui {

//! GUI window
class IGUIWindow : public IGUIElement {
public:
	virtual ~IGUIWindow() {};
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIWindow_
