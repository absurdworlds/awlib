/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_EventManager_impl_
#define _aw_EventManager_impl_
#include <vector>

#include <aw/platform/time.h>
#include <awrts/game/EventManager.h>
#include <awrts/game/Thinking.h>

namespace aw {
namespace game {
namespace impl_ {
class EventManager : public game::EventManager {
public:
	virtual ~EventManager()
	{

	}
	virtual u32 addEvent(Event event)
	{
		events_.push_back(event);
		return events_.size()-1;
	}
	virtual void removeEvent(u32 eventId)
	{
	}

	virtual void advance();
private:
	std::vector<Event> events_;
};

} // namespace impl_
} // namespace game
} // namespace aw
#endif//_aw_EventManager_impl_

