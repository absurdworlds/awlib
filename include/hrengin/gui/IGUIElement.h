#ifndef _hrengin_IGUIElement_
#define _hrengin_IGUIElement_

#include <hrengin/common/types.h>

namespace hrengin {
namespace gui {

class IGUIElement {
public:
	virtual ~IGUIElement() {};

	virtual u32 getId() const = 0;
	virtual u32 getParentId() const = 0;

// Do not override for custom elements
/*
	Get pointer to underlying class
*/
	virtual void* getUnderlyingElement() const
	{
		return 0;
	}
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIElement_
