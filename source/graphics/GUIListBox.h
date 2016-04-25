/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIListBox_
#define _aw_GUIListBox_

#include <aw/gui/GUIListBox.h>

namespace irr {
namespace gui {
class GUIListBox;
}
}

namespace aw {
namespace gui {

class GUIListBox : public GUIListBox {
public:
	GUIListBox(irr::gui::IGUIListBox* elem);
	virtual ~GUIListBox();

	virtual u32 getId() const;
	virtual u32 getParentId() const;

	virtual u32 addItem(std::string text);

	virtual std::string getText() const;
	virtual void setText(std::string text);

	virtual void* getUnderlyingElement() const
	{
		return (void*) irrElement_;
	}

private:
	void adjustScrollPosition();

	irr::gui::IGUIListBox* irrElement_;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUIListBox_
