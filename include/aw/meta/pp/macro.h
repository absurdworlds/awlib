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
#include <aw/config.h>

/*! Stringize */
#define TO_STR(x) TO_STR1(x)
#define TO_STR1(x) #x

/*! Concatenate */
#define CONCAT(x, y)   CONCAT1(x, y)
#define CONCAT1(x, y)  CONCAT2(x, y)
#define CONCAT2(x, y)  x##y

/*!
 * Forces macro expansion:
 *
 * `SEP_SPACE TUPLE(a,b)` will turn into `IDENTITY2 (a,b)`
 * but
 * `EXPAND( SEP_SPACE TUPLE(a,b) )` will expand into `a b`
 */
#define EXPAND(x) x

/*!
 * Call macro NAME with arguments __VA_ARGS__:
 *
 * `APPLY( FUNC, a, b, c)` expands into `FUNC(a,b,c)`
 */
#define APPLY(NAME,...) NAME(__VA_ARGS__)

/*!
 * Defer macro expansion:
 *
 * `APPLY(SEP_SPACE, (a,b))` will try to call `SEP_SPACE((a,b))`
 * but
 * `APPLY(SEP_SPACE DEFER, (a,b))` will expand into `SEP_SPACE (a,b)`
 * which can then be expanded with `EXPAND()` macro
 */
#define DEFER(x) x EMPTY()
#define EMPTY()

#endif//aw_pp_macro_h