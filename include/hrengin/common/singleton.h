#ifndef _hrengin_singleton_
#define _hrengin_singleton_

namespace hrengin {

template <class C>
inline C& makeSingleton() {
	static C singleton;
	return singleton;
}

} // namespace hrengin

#endif//_hrengin_singleton_
