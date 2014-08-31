#ifndef _hrengin_IGUIWindow_
#define _hrengin_IGUIWindow_

#include <hrengin/gui/IGUIElement.h>

namespace hrengin {
namespace gui {

class IGUIWindow : public IGUIElement {
public:
	virtual ~IGUIWindow() {};

	/* Get pointer to underlying class */
	virtual void* getUnderlyingElement() const = 0;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIWindow_
