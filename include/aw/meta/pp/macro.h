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

/*! Insert both arguments separated by space */
#define SEP_SPACE(x, y) x y
/*! Insert both arguments separated by semicolon */
#define SEP_SEMI(x, y) x; y
/*! Insert both arguments separated by comma */
#define SEP_COMMA(x, y) x, y


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

/*! Encases arguments in (), allowing to be passed as a single argument */
#define TUPLE(...) (__VA_ARGS__)

/*!
 * Same as apply, but for a TUPLE:
 * `APPLY_T( FUNC, TUPLE(a,b,c) )` expands into `FUNC(a,b,c)`
 */
#define APPLY_T(NAME,x) EXPAND( NAME x )

#define IDENTITY(...) __VA_ARGS__

#define UNPACK(x) APPLY_T( IDENTITY, x )

#define FIRST(x,y)  x
#define SECOND(x,y) y

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
