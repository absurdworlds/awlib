/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hidden_impl_
#define _hrengin_hidden_impl_

#define DECLARE_HIDDEN_DETAILS(CLASSNAME) \
	class Details; \
	virtual CLASSNAME::Details* getDetails() {return 0;}

#endif//_hrengin_hidden_impl_
