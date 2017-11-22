/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_pp_for_each_h
#define aw_meta_pp_for_each_h
//#include <aw/meta/pp/macro.h>
#include "macro.h"

/*! Vararg processing macros
 * Uses the trick: depending on number of arguments, the desired macro shifts
 * to a NAME position.
 *
 * Use FOR_EACH macro, other macros are to be used only internally by FOR_EACH.
 * To process more arguments, add another FE_ macro and add more arguments to
 * GET_MACRO
 */
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME

#define FE_1(DO, X, ...) EXPAND(DO(X))
#define FE_2(DO, X, ...) EXPAND(DO(X)FE_1(DO, __VA_ARGS__))
#define FE_3(DO, X, ...) EXPAND(DO(X)FE_2(DO, __VA_ARGS__))
#define FE_4(DO, X, ...) EXPAND(DO(X)FE_3(DO, __VA_ARGS__))
#define FE_5(DO, X, ...) EXPAND(DO(X)FE_4(DO, __VA_ARGS__))
#define FE_6(DO, X, ...) EXPAND(DO(X)FE_5(DO, __VA_ARGS__))
#define FE_7(DO, X, ...) EXPAND(DO(X)FE_6(DO, __VA_ARGS__))
#define FE_8(DO, X, ...) EXPAND(DO(X)FE_7(DO, __VA_ARGS__))

#define FOR_EACH(NAME,...) \
        EXPAND( \
               GET_MACRO(__VA_ARGS__, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1) \
               (NAME, __VA_ARGS__) \
        )
#endif//aw_meta_pp_for_each_h
