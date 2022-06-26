/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_pp_macro_h
#define aw_pp_macro_h
//#include <aw/config.h>

/*! Stringize */
#define AW_TO_STR(...) AW_TO_STR_(__VA_ARGS__)
#define AW_TO_STR_(...) #__VA_ARGS__

/*! Concatenate */
#define AW_CONCAT(x, y)   AW_CONCAT_(x, y)
#define AW_CONCAT_(x, y)  x##y

#define AW_CONCAT2(x, y)    AW_CONCAT(x, y)
#define AW_CONCAT3(x, y, z) AW_CONCAT(AW_CONCAT(x, y), z)

/*!
 * Forces macro expansion:
 *
 * `AW_SEP_SPACE AW_TUPLE(a,b)` will turn into `AW_SEP_SPACE (a,b)`
 * but
 * `AW_EXPAND( AW_SEP_SPACE AW_TUPLE(a,b) )` will expand into `a b`
 */
#define AW_EXPAND(...) __VA_ARGS__
#define AW_IDENTITY(...) __VA_ARGS__

/*!
 * Call macro NAME with arguments __VA_ARGS__:
 *
 * `AW_APPLY( FUNC, a, b, c)` expands into `FUNC(a,b,c)`
 */
#define AW_APPLY(NAME,...) NAME(__VA_ARGS__)

#define AW_APPLY_EXPAND(NAME,...) AW_EXPAND(NAME(__VA_ARGS__))
#define AW_APPLY_EXPAND2(NAME,...) AW_EXPAND(NAME(__VA_ARGS__))

/*!
 * Defer macro expansion:
 *
 * `AW_APPLY(AW_SEP_SPACE, (a,b))` will try to call `AW_SEP_SPACE((a,b))`
 * but
 * `AW_APPLY(AW_SEP_SPACE AW_DEFER, (a,b))` will expand into `AW_SEP_SPACE (a,b)`
 * which can then be expanded with `AW_EXPAND()` macro
 */
#define AW_DEFER(x) x AW_EMPTY()
#define AW_EMPTY()

#define AW_EAT(...)

#endif//aw_pp_macro_h
