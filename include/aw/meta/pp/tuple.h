/*
 * Copyright (C) 2017  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pp_tuple_h
#define aw_pp_tuple_h

#include "macro.h"

/*! Encases arguments in (), allowing to be passed as a single argument */
#define TUPLE(...) (__VA_ARGS__)

/*!
 * Same as apply, but for a TUPLE:
 * `APPLY_T( FUNC, TUPLE(a,b,c) )` expands into `FUNC(a,b,c)`
 */
#define APPLY_T(NAME,x) EXPAND( NAME x )

#define UNPACK(x) APPLY_T( IDENTITY, x )

#define FIRST(x,...)    x
#define SECOND(x,y,...) y
#define REST(x,...)     __VA_ARGS__
#define TAIL(x,...)     __VA_ARGS__

#endif//aw_pp_tupl_h
