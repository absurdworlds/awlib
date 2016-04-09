#ifndef aw_signals_multi_threaded_h
#define aw_signals_multi_threaded_h

#ifdef aw_signals_single_threaded_h
#error "Single-threaded and multi-threaded signals cannot be used together."
#endif

#include "signal.h"

namespace aw {
namespace signals {
struct multi_threaded {
	using lock_type = std::unique_lock<std::mutex>;

	lock_type lock()
	{
		return lock_type(mtx);
	}

	std::mutex mtx;
};

using slot = impl::slot<multi_threaded>;

template<class signature>
using signal = impl::signal<multi_threaded, signature>;
} // namespace signals
} // namespace aw
#endif //aw_signals_multi_threaded_h
