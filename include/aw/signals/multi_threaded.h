/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_multi_threaded_h
#define aw_signals_multi_threaded_h

#ifdef aw_signals_single_threaded_h
#error "Single-threaded and multi-threaded signals cannot be used together."
#endif

#include <mutex>
#include "signal.h"

namespace aw {
namespace signals {
inline namespace v1 {
struct multi_threaded {
	using mutex_type  = std::mutex;
	using lock_type   = std::lock_guard<multi_threaded>;
	using lock_n_type = std::lock_guard<multi_threaded, multi_threaded>;

	void lock()
	{
		mtx.lock();
	}

	void unlock()
	{
		mtx.unlock();
	}

	mutex_type mtx;
};

using observer = impl::observer<multi_threaded>;

template<class signature>
using signal = impl::signal<multi_threaded, signature>;
} // namespace v1
} // namespace signals
} // namespace aw
#endif //aw_signals_multi_threaded_h
