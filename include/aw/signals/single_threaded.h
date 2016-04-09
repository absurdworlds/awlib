#ifndef aw_signals_single_threaded_h
#define aw_signals_single_threaded_h

#ifdef aw_signals_multi_threaded_h
#error "Single-threaded and multi-threaded signals cannot be used together."
#endif

#include "signal.h"

namespace aw {
namespace signals {
struct single_threaded {
	struct lock_dummy {};
	struct mutex_dummy {};

	using lock_type = lock_dummy;

	lock_type lock()
	{
		return lock_dummy{};
	}
};

using slot = impl::slot<single_threaded>;

template<class signature>
using signal = impl::signal<single_threaded, signature>;
} // namespace signals
} // namespace aw
#endif//aw_signals_single_threaded_h
