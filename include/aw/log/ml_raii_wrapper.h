/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_RAIILogWrapper_h
#define aw_RAIILogWrapper_h
#include <aw/types/traits/basic_traits.h>
#include <aw/logger/MultiLog.h>
namespace aw {
inline namespace log {
/*!
 * Automatically adds and removes itself to/from MultiLog.
 */
template<class LogType>
struct RAIILog : LogType {
	static_assert(is_base_of<Log, LogType>,
	              "RAIILogWrapper must be derived from aw::Log");

	RAIILog(MultiLog& sender)
		: sender(sender)
	{
		sender.add(*this);
	}

	~RAIILog()
	{
		sender.remove(*this);
	}

private:
	MultiLog& sender;
};
} // namespace log
} // namespace aw
#endif//aw_RAIILogWrapper_h
