/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_signals_single_threaded_h
#define aw_signals_single_threaded_h

#ifdef aw_signals_multi_threaded_h
#error "Single-threaded and multi-threaded signals cannot be used together."
#endif

#include "signal.h"

namespace aw {
namespace signals {
inline namespace v1 {
struct single_threaded {
	struct mutex_dummy {};

	template<class...Mutex>
	struct lock_dummy {
		lock_dummy(Mutex const&...)
		{}
	};

	using mutex_type = mutex_dummy;

	using lock_type    = lock_dummy<single_threaded>;
	using lock_n_type  = lock_dummy<single_threaded, single_threaded>;

	void lock()
	{ }

	void unlock()
	{ }
};

using observer = impl::observer<single_threaded>;

using connection = impl::connection<single_threaded>;

template<class signature>
using signal = impl::signal<single_threaded, signature>;
} // namespace v1
} // namespace signals
} // namespace aw
#endif//aw_signals_single_threaded_h
