#ifndef _hrengin_IGUIElement_
#define _hrengin_IGUIElement_

#include <string>

#include <hrengin/common/types.h>

namespace hrengin {
namespace gui {

class IGUIElement {
public:
	virtual ~IGUIElement() {};

	virtual u32 getId() const = 0;
	virtual u32 getParentId() const = 0;

	#if 0
	virtual void setAbsolutePosition(Vector2d<i32> position) = 0;
	virtual void setRelativePosition(Vector2d<i32> position) = 0;
	virtual void setAbsoluteRect(Rect<i32> rect) = 0;
	virtual void setRelativeRect(Rect<i32> rect) = 0;


	#endif
	/* get the caption of this element */
	virtual std::string getText() const = 0;

	virtual void* getUnderlyingElement() const = 0;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIElement_
