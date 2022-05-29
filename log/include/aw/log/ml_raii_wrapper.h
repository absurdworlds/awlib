/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_log_ml_raii_wrapper_h
#define aw_log_ml_raii_wrapper_h
#include <aw/types/traits/basic_traits.h>
#include <aw/log/multi_log.h>
namespace aw {
inline namespace v1 {
/*!
 * Automatically adds and removes itself to/from MultiLog.
 */
template<class LogType>
struct raii_log : LogType {
	static_assert(is_base_of<log, LogType>,
	              "LogType must be derived from aw::log");

	template<typename...Args>
	raii_log(multi_log& sender, Args&&...args)
		: LogType{std::forward<Args>(args)...}, sender{sender}
	{
		sender.add(*this);
	}

	~raii_log()
	{
		sender.remove(*this);
	}

private:
	multi_log& sender;
};
} // namespace v1
} // namespace aw
#endif//aw_RAIILogWrapper_h
