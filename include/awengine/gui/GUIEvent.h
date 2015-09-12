/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_GUIEvent_
#define _awrts_GUIEvent_
#include <awengine/common/types.h>
#include <awengine/common/Event.h>
#include <awengine/gui/Element.h>
namespace awrts {
namespace gui {

struct GUIEvent : public EventId<GUIEvent>{
public:
	enum Action {
		Unknown,
		Closed,
		Hovered,
		Left,
		Focused,
		Unfocused,
		FocusLost = Unfocused,
	};

	Action action;
};

} // namespace gui
} // namespace awrts
#endif //_awrts_GUIEvent_
