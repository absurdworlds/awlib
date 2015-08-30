/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUIElement_
#define _awrts_GUIElement_

#include <string>

#include <awrts/common/types.h>
#include <awrts/common/hidden_impl.h>

namespace awrts {
namespace gui {

//! Base class for GUI elements
class GUIElement {
public:
	//! Virtual destructor
	virtual ~GUIElement() {};

	virtual u32 getId() const = 0;
	virtual u32 getParentId() const = 0;

#if 0
	virtual void setAbsolutePosition(Vector2d<i32> position) = 0;
	virtual void setRelativePosition(Vector2d<i32> position) = 0;
	virtual void setAbsoluteRect(Rect<i32> rect) = 0;
	virtual void setRelativeRect(Rect<i32> rect) = 0;
#endif

	//! Get caption of the element
	virtual std::string getText() const = 0;

	//! Set caption of the element
	virtual void setText(std::string text) = 0;

	virtual void* getUnderlyingElement() const = 0;

	//! Internal implementation details
	DECLARE_HIDDEN_DETAILS(GUIElement);
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIElement_
