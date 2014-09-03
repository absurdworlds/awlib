#ifndef _hrengin_IGUIListBox_
#define _hrengin_IGUIListBox_

#include <string>

#include <hrengin/gui/IGUIElement.h>

namespace hrengin {
namespace gui {

class IGUIListBox : public IGUIElement {
public:
	virtual ~IGUIListBox() {};

	/* Add an item to list 
	   @return: Item id
	 */
	virtual u32 addItem(std::string text) = 0;
};

} // namespace gui
} // namespace hrengin

#endif //_hrengin_IGUIListBox_
