/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
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
