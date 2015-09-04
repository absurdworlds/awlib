/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUI_Manager_
#define _awrts_GUI_Manager_

#include <awrts/math/Rect.h>

namespace awrts {
namespace gui {
class Element;

class Root {
public:
	virtual ~Root() {};

	virtual void draw() = 0;

	virtual void addElement(Element* element);
	virtual Element* getActiveElement(Element* element);
};

std::unique_ptr<Root> createRoot(input::Relay* input);


} // namespace gui
} // namespace awrts
#endif //_awrts_GUI_Manager_
