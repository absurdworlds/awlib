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
#define AW_TUPLE(...) (__VA_ARGS__)

/*!
 * Same as apply, but for a TUPLE:
 * `AW_APPLY_T( FUNC, AW_TUPLE(a,b,c) )` expands into `FUNC(a,b,c)`
 */
#define AW_APPLY_T(NAME,x) AW_EXPAND( NAME x )

#define AW_UNPACK(x) AW_APPLY_T( AW_IDENTITY, x )

#define AW_FIRST(x,...)    x
#define AW_SECOND(x,y,...) y
#define AW_REST(x,...)     __VA_ARGS__
#define AW_TAIL(x,...)     __VA_ARGS__

//! Combine two tuples
#define AW_COMBINE( T1, T2 ) (AW_UNPACK(T1),AW_UNPACK(T2))

#endif//aw_pp_tupl_h
